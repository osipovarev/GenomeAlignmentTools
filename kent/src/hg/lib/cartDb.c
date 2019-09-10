/* cartDb.c was originally generated by the autoSql program, which also 
 * generated cartDb.h and cartDb.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */


/*
 *  TODO REMOVE AFTER AUTOUPGRADE COMPLETE: (added 2014-03-09)
 *
 * autoupgrade of the userDb and sessionDb tables
 *   alter table userDb    add column sessionKey varchar(255) NOT NULL default '';
 *   alter table sessionDb add column sessionKey varchar(255) NOT NULL default '';
 *
 */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "hgConfig.h"
#include "base64.h"
#include "cartDb.h"
#include "cart.h"
#include "autoUpgrade.h"

extern DbConnector cartDefaultConnector;
extern DbDisconnect cartDefaultDisconnector;

static boolean userDbInitialized = FALSE;
static boolean sessionDbInitialized = FALSE;

boolean cartDbHasSessionKey(struct sqlConnection *conn, char *table)
/* Check to see if the table has the sessionKey field */
{
static boolean userDbHasSessionKey = FALSE;
static boolean sessionDbHasSessionKey = FALSE;
if (sameString(table, userDbTable()))
    {
    if (!userDbInitialized)
	{
	userDbInitialized = TRUE;
	if (sqlFieldIndex(conn, table, "sessionKey") >= 0)
	    {
	    userDbHasSessionKey = TRUE;
	    } 
	}
    return userDbHasSessionKey;
    }
else if (sameString(table, sessionDbTable()))
    {
    if (!sessionDbInitialized)
	{
	sessionDbInitialized = TRUE;
	if (sqlFieldIndex(conn, table, "sessionKey") >= 0)
	    {
	    sessionDbHasSessionKey = TRUE;
	    } 
	}
    return sessionDbHasSessionKey;
    }
else
    errAbort("Unknown table %s", table);
return FALSE;
}

boolean cartDbUseSessionKey()
/* Check settings and and state to determine if sessionKey is in use */
{
static boolean initialized = FALSE;
static boolean useSessionKey = FALSE;
if (!initialized)
    {
    initialized = TRUE;
    char *sessionKey = cfgOption2("browser", "sessionKey");
    if (!sessionKey)
	sessionKey = "on";  // DEFAULT but this might change to another value
    if (sameString(sessionKey, "on"))
	{
	useSessionKey = TRUE;
	struct sqlConnection *conn = cartDefaultConnector();
	boolean userDbHasSessionKey = cartDbHasSessionKey(conn, userDbTable());
	boolean sessionDbHasSessionKey = cartDbHasSessionKey(conn, sessionDbTable());
	if ( ! (userDbHasSessionKey && sessionDbHasSessionKey) )
	    {
    	    //errAbort("brower.sessionKey=on but userDb and sessionDb are missing the sessionKey field.");
	    // AUTO-UPGRADE tables to add missing sessionKey field here.
	    if (!userDbHasSessionKey)
		{
                autoUpgradeTableAddColumn(conn, userDbTable(), "sessionKey",
                                          "varchar(255)", TRUE, "''");
		userDbInitialized = FALSE;
		userDbHasSessionKey = cartDbHasSessionKey(conn, userDbTable());
		}
    	    if (!sessionDbHasSessionKey)
		{
                autoUpgradeTableAddColumn(conn, sessionDbTable(), "sessionKey",
                                          "varchar(255)", TRUE, "''");
		sessionDbInitialized = FALSE;
		sessionDbHasSessionKey = cartDbHasSessionKey(conn, sessionDbTable());
		}
	    if ( ! (userDbHasSessionKey && sessionDbHasSessionKey) )
		useSessionKey = FALSE;
	    }
	cartDefaultDisconnector(&conn);
	}
    else if (sameString(sessionKey, "off"))
	{
	useSessionKey = FALSE;
	}
    else if (sameString(sessionKey, "autodetect"))
	{
	errAbort("brower.sessionKey=autodetect has not implemented yet."); // TODO
	}
    }
return useSessionKey;
}

void cartDbSecureId(char *buf, int bufSize, struct cartDb *cartDb)
/* Return combined string of session id plus sessionKey in buf if turned on.*/
{
if (cartDbUseSessionKey() && !sameString(cartDb->sessionKey,""))
    safef(buf, bufSize, "%d_%s", cartDb->id, cartDb->sessionKey);
else
    safef(buf, bufSize, "%d", cartDb->id);
}

unsigned int cartDbParseId(char *id, char **pSessionKey)
/* Parse out the numeric id and id_sessionKey string if present. */
{
unsigned int result = 0;
if (sameString(id,"")) // some users reported blank cookie values.
    {
    verbose(1, "cartDbParseId: id with empty string found.");
    if (pSessionKey)
	*pSessionKey = NULL;
    return 0;
    }
char *e = strchr(id, '_');
if (e)
    *e = 0;
result = sqlUnsigned(id);
if (e)
    {
    *e = '_';
    if (pSessionKey)
	*pSessionKey = e+1;
    }
else
    {
    if (pSessionKey)
	*pSessionKey = NULL;
    }
return result;
}


void cartDbStaticLoad(char **row, struct cartDb *ret)
/* Load a row from cartDb table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = sqlUnsigned(row[0]);
ret->contents = row[1];
ret->reserved = sqlSigned(row[2]);
ret->firstUse = row[3];
ret->lastUse = row[4];
ret->useCount = sqlSigned(row[5]);
if (cartDbUseSessionKey())
    ret->sessionKey = row[6];
}

struct cartDb *cartDbLoad(char **row)
/* Load a cartDb from row fetched with select * from cartDb
 * from database.  Dispose of this with cartDbFree(). */
{
struct cartDb *ret;

AllocVar(ret);
ret->id = sqlUnsigned(row[0]);
ret->contents = cloneString(row[1]);
ret->reserved = sqlSigned(row[2]);
ret->firstUse = cloneString(row[3]);
ret->lastUse = cloneString(row[4]);
ret->useCount = sqlSigned(row[5]);
if (cartDbUseSessionKey())
    ret->sessionKey = cloneString(row[6]);
return ret;
}

struct cartDb *cartDbLoadAll(char *fileName) 
/* Load all cartDb from a tab-separated file.
 * Dispose of this with cartDbFreeList(). */
{
struct cartDb *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileRow(lf, row))
    {
    el = cartDbLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct cartDb *cartDbLoadWhere(struct sqlConnection *conn, char *table, char *where)
/* Load all cartDb from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with cartDbFreeList(). */
{
struct cartDb *list = NULL, *el;
struct dyString *query = dyStringNew(256);
struct sqlResult *sr;
char **row;

sqlDyStringPrintf(query, "select * from %s", table);
if (where != NULL)
    dyStringPrintf(query, " where %-s", where); // the where clause must be checked by caller for sqli
sr = sqlGetResult(conn, query->string);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = cartDbLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
dyStringFree(&query);
return list;
}

struct cartDb *cartDbCommaIn(char **pS, struct cartDb *ret)
/* Create a cartDb out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new cartDb */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
ret->contents = sqlStringComma(&s);
ret->reserved = sqlSignedComma(&s);
ret->firstUse = sqlStringComma(&s);
ret->lastUse = sqlStringComma(&s);
ret->useCount = sqlSignedComma(&s);
if (cartDbUseSessionKey())
    ret->sessionKey = sqlStringComma(&s);
*pS = s;
return ret;
}

void cartDbFree(struct cartDb **pEl)
/* Free a single dynamically allocated cartDb such as created
 * with cartDbLoad(). */
{
struct cartDb *el;

if ((el = *pEl) == NULL) return;
freeMem(el->contents);
freeMem(el->firstUse);
freeMem(el->lastUse);
if (cartDbUseSessionKey())
    freeMem(el->sessionKey);
freez(pEl);
}

void cartDbFreeList(struct cartDb **pList)
/* Free a list of dynamically allocated cartDb's */
{
struct cartDb *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    cartDbFree(&el);
    }
*pList = NULL;
}

void cartDbOutput(struct cartDb *el, FILE *f, char sep, char lastSep) 
/* Print out cartDb.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%u", el->id);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->contents);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->reserved);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->firstUse);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->lastUse);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->useCount);
if (cartDbUseSessionKey())
    {
    fputc(sep,f);
    fprintf(f, "%s", el->sessionKey);
    }
fputc(lastSep,f);
}

char *userDbTable()
/* Return the name of the userDb table. */
{
static char *userDbTable = NULL;
if (userDbTable == NULL)
    userDbTable = cfgOptionEnvDefault("HGDB_USERDBTABLE",
	    userDbTableConfVariable, defaultUserDbTableName);
return userDbTable;
}

char *sessionDbTable()
/* Return the name of the sessionDb table. */
{
static char *sessionDbTable = NULL;
if (sessionDbTable == NULL)
    sessionDbTable = cfgOptionEnvDefault("HGDB_SESSIONDBTABLE",
	    sessionDbTableConfVariable, defaultSessionDbTableName);
return sessionDbTable;
}

