/* celeraCoverage.c was originally generated by the autoSql program, which also 
 * generated celeraCoverage.h and celeraCoverage.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "celeraCoverage.h"


void celeraCoverageStaticLoad(char **row, struct celeraCoverage *ret)
/* Load a row from celeraCoverage table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
}

struct celeraCoverage *celeraCoverageLoad(char **row)
/* Load a celeraCoverage from row fetched with select * from celeraCoverage
 * from database.  Dispose of this with celeraCoverageFree(). */
{
struct celeraCoverage *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
return ret;
}

struct celeraCoverage *celeraCoverageLoadAll(char *fileName) 
/* Load all celeraCoverage from a tab-separated file.
 * Dispose of this with celeraCoverageFreeList(). */
{
struct celeraCoverage *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileRow(lf, row))
    {
    el = celeraCoverageLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct celeraCoverage *celeraCoverageLoadWhere(struct sqlConnection *conn, char *table, char *where)
/* Load all celeraCoverage from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with celeraCoverageFreeList(). */
{
struct celeraCoverage *list = NULL, *el;
struct dyString *query = dyStringNew(256);
struct sqlResult *sr;
char **row;

sqlDyStringPrintf(query, "select * from %s", table);
if (where != NULL)
    dyStringPrintf(query, " where %s", where);
sr = sqlGetResult(conn, query->string);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = celeraCoverageLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
dyStringFree(&query);
return list;
}

struct celeraCoverage *celeraCoverageCommaIn(char **pS, struct celeraCoverage *ret)
/* Create a celeraCoverage out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new celeraCoverage */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
*pS = s;
return ret;
}

void celeraCoverageFree(struct celeraCoverage **pEl)
/* Free a single dynamically allocated celeraCoverage such as created
 * with celeraCoverageLoad(). */
{
struct celeraCoverage *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freez(pEl);
}

void celeraCoverageFreeList(struct celeraCoverage **pList)
/* Free a list of dynamically allocated celeraCoverage's */
{
struct celeraCoverage *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    celeraCoverageFree(&el);
    }
*pList = NULL;
}

void celeraCoverageOutput(struct celeraCoverage *el, FILE *f, char sep, char lastSep) 
/* Print out celeraCoverage.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStart);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

