/* mouseSynWhd.h was originally generated by the autoSql program, which also 
 * generated mouseSynWhd.c and mouseSynWhd.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2002 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef MOUSESYNWHD_H
#define MOUSESYNWHD_H

struct mouseSynWhd
/* Whitehead Synteny between mouse and human chromosomes (bed 6 +). */
    {
    struct mouseSynWhd *next;  /* Next in singly linked list. */
    char *chrom;	/* Human chromosome */
    unsigned chromStart;	/* Start position in human chromosome */
    unsigned chromEnd;	/* End position in human chromosome */
    char *name;	/* Name of mouse chromosome */
    unsigned score;	/* Unused (bed 6 compatibility) */
    char strand[2];	/* + or - */
    unsigned mouseStart;	/* Start position in mouse chromosome */
    unsigned mouseEnd;	/* End position in mouse chromosome */
    char *segLabel;	/* Whitehead segment label */
    };

void mouseSynWhdStaticLoad(char **row, struct mouseSynWhd *ret);
/* Load a row from mouseSynWhd table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct mouseSynWhd *mouseSynWhdLoad(char **row);
/* Load a mouseSynWhd from row fetched with select * from mouseSynWhd
 * from database.  Dispose of this with mouseSynWhdFree(). */

struct mouseSynWhd *mouseSynWhdLoadAll(char *fileName);
/* Load all mouseSynWhd from a tab-separated file.
 * Dispose of this with mouseSynWhdFreeList(). */

struct mouseSynWhd *mouseSynWhdLoadWhere(struct sqlConnection *conn, char *table, char *where);
/* Load all mouseSynWhd from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with mouseSynWhdFreeList(). */

struct mouseSynWhd *mouseSynWhdCommaIn(char **pS, struct mouseSynWhd *ret);
/* Create a mouseSynWhd out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new mouseSynWhd */

void mouseSynWhdFree(struct mouseSynWhd **pEl);
/* Free a single dynamically allocated mouseSynWhd such as created
 * with mouseSynWhdLoad(). */

void mouseSynWhdFreeList(struct mouseSynWhd **pList);
/* Free a list of dynamically allocated mouseSynWhd's */

void mouseSynWhdOutput(struct mouseSynWhd *el, FILE *f, char sep, char lastSep);
/* Print out mouseSynWhd.  Separate fields with sep. Follow last field with lastSep. */

#define mouseSynWhdTabOut(el,f) mouseSynWhdOutput(el,f,'\t','\n');
/* Print out mouseSynWhd as a line in a tab-separated file. */

#define mouseSynWhdCommaOut(el,f) mouseSynWhdOutput(el,f,',',',');
/* Print out mouseSynWhd as a comma separated list including final comma. */

#endif /* MOUSESYNWHD_H */

