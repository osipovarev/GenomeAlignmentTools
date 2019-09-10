/* rmskJoined.h was originally generated by the autoSql program, which also 
 * generated rmskJoined.c and rmskJoined.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2013 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef RMSKJOINED_H
#define RMSKJOINED_H

#define RMSKJOINED_NUM_COLS 14

struct rmskJoined
/* RepeatMasker joined annotation record */
    {
    struct rmskJoined *next;  /* Next in singly linked list. */
    char *chrom;	/* Reference sequence chromosome or scaffold */
    unsigned chromStart;	/* Start position of feature in chromosome */
    unsigned chromEnd;	/* End position feature in chromosome */
    char *name;	/* Short Name of item */
    unsigned score;	/* Score from 0-1000 */
    char strand[2];	/* + or - */
    unsigned alignStart;	/* Start position of aligned portion of feature */
    unsigned alignEnd;	/* End position of aligned portion of feature */
    unsigned reserved;	/* Used as itemRgb */
    int blockCount;	/* Number of blocks */
    int *blockSizes;	/* Comma separated list of block sizes */
    int *blockRelStarts;	/* Start positions rel. to chromStart or -1 for unaligned blocks */
    char *id;	/* ID to bed used in URL to link back */
    char *description;	/* Long description of item for the details page */
    };

struct rmskJoined *rmskJoinedLoad(char **row);
/* Load a rmskJoined from row fetched with select * from rmskJoined
 * from database.  Dispose of this with rmskJoinedFree(). */

struct rmskJoined *rmskJoinedLoadAll(char *fileName);
/* Load all rmskJoined from whitespace-separated file.
 * Dispose of this with rmskJoinedFreeList(). */

struct rmskJoined *rmskJoinedLoadAllByChar(char *fileName, char chopper);
/* Load all rmskJoined from chopper separated file.
 * Dispose of this with rmskJoinedFreeList(). */

#define rmskJoinedLoadAllByTab(a) rmskJoinedLoadAllByChar(a, '\t');
/* Load all rmskJoined from tab separated file.
 * Dispose of this with rmskJoinedFreeList(). */

struct rmskJoined *rmskJoinedCommaIn(char **pS, struct rmskJoined *ret);
/* Create a rmskJoined out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new rmskJoined */

void rmskJoinedFree(struct rmskJoined **pEl);
/* Free a single dynamically allocated rmskJoined such as created
 * with rmskJoinedLoad(). */

void rmskJoinedFreeList(struct rmskJoined **pList);
/* Free a list of dynamically allocated rmskJoined's */

void rmskJoinedOutput(struct rmskJoined *el, FILE *f, char sep, char lastSep);
/* Print out rmskJoined.  Separate fields with sep. Follow last field with lastSep. */

#define rmskJoinedTabOut(el,f) rmskJoinedOutput(el,f,'\t','\n');
/* Print out rmskJoined as a line in a tab-separated file. */

#define rmskJoinedCommaOut(el,f) rmskJoinedOutput(el,f,',',',');
/* Print out rmskJoined as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* RMSKJOINED_H */

