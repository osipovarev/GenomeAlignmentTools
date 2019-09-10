/* ecCode.c was originally generated by the autoSql program, which also 
 * generated ecCode.h and ecCode.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "ecCode.h"


void ecCodeStaticLoad(char **row, struct ecCode *ret)
/* Load a row from ecCode table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->level1 = sqlUnsigned(row[0]);
ret->level2 = sqlUnsigned(row[1]);
ret->level3 = sqlUnsigned(row[2]);
ret->level4 = sqlUnsigned(row[3]);
ret->ec = row[4];
ret->description = row[5];
}

struct ecCode *ecCodeLoad(char **row)
/* Load a ecCode from row fetched with select * from ecCode
 * from database.  Dispose of this with ecCodeFree(). */
{
struct ecCode *ret;

AllocVar(ret);
ret->level1 = sqlUnsigned(row[0]);
ret->level2 = sqlUnsigned(row[1]);
ret->level3 = sqlUnsigned(row[2]);
ret->level4 = sqlUnsigned(row[3]);
ret->ec = cloneString(row[4]);
ret->description = cloneString(row[5]);
return ret;
}

struct ecCode *ecCodeLoadAll(char *fileName) 
/* Load all ecCode from a whitespace-separated file.
 * Dispose of this with ecCodeFreeList(). */
{
struct ecCode *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileRow(lf, row))
    {
    el = ecCodeLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct ecCode *ecCodeLoadAllByChar(char *fileName, char chopper) 
/* Load all ecCode from a chopper separated file.
 * Dispose of this with ecCodeFreeList(). */
{
struct ecCode *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[6];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = ecCodeLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct ecCode *ecCodeCommaIn(char **pS, struct ecCode *ret)
/* Create a ecCode out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new ecCode */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->level1 = sqlUnsignedComma(&s);
ret->level2 = sqlUnsignedComma(&s);
ret->level3 = sqlUnsignedComma(&s);
ret->level4 = sqlUnsignedComma(&s);
ret->ec = sqlStringComma(&s);
ret->description = sqlStringComma(&s);
*pS = s;
return ret;
}

void ecCodeFree(struct ecCode **pEl)
/* Free a single dynamically allocated ecCode such as created
 * with ecCodeLoad(). */
{
struct ecCode *el;

if ((el = *pEl) == NULL) return;
freeMem(el->ec);
freeMem(el->description);
freez(pEl);
}

void ecCodeFreeList(struct ecCode **pList)
/* Free a list of dynamically allocated ecCode's */
{
struct ecCode *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    ecCodeFree(&el);
    }
*pList = NULL;
}

void ecCodeOutput(struct ecCode *el, FILE *f, char sep, char lastSep) 
/* Print out ecCode.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->level1);
fputc(sep,f);
fprintf(f, "%u", el->level2);
fputc(sep,f);
fprintf(f, "%u", el->level3);
fputc(sep,f);
fprintf(f, "%u", el->level4);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->ec);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->description);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

