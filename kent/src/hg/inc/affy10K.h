/* affy10K.h was originally generated by the autoSql program, which also 
 * generated affy10K.c and affy10K.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2013 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef AFFY10K_H
#define AFFY10K_H

#ifndef JKSQL_H
#include "jksql.h"
#endif

#define AFFY10K_NUM_COLS 4

struct affy10K
/* Information from affy10K representing the Affymetrix 10K Mapping array */
    {
    struct affy10K *next;  /* Next in singly linked list. */
    char *chrom;	/*   */
    unsigned chromStart;	/*   */
    unsigned chromEnd;	/*   */
    unsigned affyId;	/* Affymetrix SNP id */
    };

void affy10KStaticLoad(char **row, struct affy10K *ret);
/* Load a row from affy10K table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct affy10K *affy10KLoad(char **row);
/* Load a affy10K from row fetched with select * from affy10K
 * from database.  Dispose of this with affy10KFree(). */

struct affy10K *affy10KLoadAll(char *fileName);
/* Load all affy10K from whitespace-separated file.
 * Dispose of this with affy10KFreeList(). */

struct affy10K *affy10KLoadAllByChar(char *fileName, char chopper);
/* Load all affy10K from chopper separated file.
 * Dispose of this with affy10KFreeList(). */

#define affy10KLoadAllByTab(a) affy10KLoadAllByChar(a, '\t');
/* Load all affy10K from tab separated file.
 * Dispose of this with affy10KFreeList(). */

struct affy10K *affy10KLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all affy10K from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with affy10KFreeList(). */

void affy10KSaveToDb(struct sqlConnection *conn, struct affy10K *el, char *tableName, int updateSize);
/* Save affy10K as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */

struct affy10K *affy10KCommaIn(char **pS, struct affy10K *ret);
/* Create a affy10K out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new affy10K */

void affy10KFree(struct affy10K **pEl);
/* Free a single dynamically allocated affy10K such as created
 * with affy10KLoad(). */

void affy10KFreeList(struct affy10K **pList);
/* Free a list of dynamically allocated affy10K's */

void affy10KOutput(struct affy10K *el, FILE *f, char sep, char lastSep);
/* Print out affy10K.  Separate fields with sep. Follow last field with lastSep. */

#define affy10KTabOut(el,f) affy10KOutput(el,f,'\t','\n');
/* Print out affy10K as a line in a tab-separated file. */

#define affy10KCommaOut(el,f) affy10KOutput(el,f,',',',');
/* Print out affy10K as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* AFFY10K_H */

