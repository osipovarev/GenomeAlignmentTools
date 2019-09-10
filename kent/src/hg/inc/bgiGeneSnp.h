/* bgiGeneSnp.h was originally generated by the autoSql program, which also 
 * generated bgiGeneSnp.c and bgiGeneSnp.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2004 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef BGIGENESNP_H
#define BGIGENESNP_H

#define BGIGENESNP_NUM_COLS 6

struct bgiGeneSnp
/* Beijing Genomics Institute Gene-SNP associations (many-to-many) */
    {
    struct bgiGeneSnp *next;  /* Next in singly linked list. */
    char *geneName;	/* Name of BGI gene. */
    char *snpName;	/* Name of BGI SNP */
    char *geneAssoc;	/* Association to gene: upstream, utr, exon, etc */
    char *effect;	/* Changes to codon or splice site (if applicable) */
    char phase[2];	/* Phase of SNP in codon (if applicable) */
    char *siftComment;	/* Comment from SIFT (if applicable) */
    };

void bgiGeneSnpStaticLoad(char **row, struct bgiGeneSnp *ret);
/* Load a row from bgiGeneSnp table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct bgiGeneSnp *bgiGeneSnpLoad(char **row);
/* Load a bgiGeneSnp from row fetched with select * from bgiGeneSnp
 * from database.  Dispose of this with bgiGeneSnpFree(). */

struct bgiGeneSnp *bgiGeneSnpLoadAll(char *fileName);
/* Load all bgiGeneSnp from whitespace-separated file.
 * Dispose of this with bgiGeneSnpFreeList(). */

struct bgiGeneSnp *bgiGeneSnpLoadAllByChar(char *fileName, char chopper);
/* Load all bgiGeneSnp from chopper separated file.
 * Dispose of this with bgiGeneSnpFreeList(). */

#define bgiGeneSnpLoadAllByTab(a) bgiGeneSnpLoadAllByChar(a, '\t');
/* Load all bgiGeneSnp from tab separated file.
 * Dispose of this with bgiGeneSnpFreeList(). */

struct bgiGeneSnp *bgiGeneSnpCommaIn(char **pS, struct bgiGeneSnp *ret);
/* Create a bgiGeneSnp out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new bgiGeneSnp */

void bgiGeneSnpFree(struct bgiGeneSnp **pEl);
/* Free a single dynamically allocated bgiGeneSnp such as created
 * with bgiGeneSnpLoad(). */

void bgiGeneSnpFreeList(struct bgiGeneSnp **pList);
/* Free a list of dynamically allocated bgiGeneSnp's */

void bgiGeneSnpOutput(struct bgiGeneSnp *el, FILE *f, char sep, char lastSep);
/* Print out bgiGeneSnp.  Separate fields with sep. Follow last field with lastSep. */

#define bgiGeneSnpTabOut(el,f) bgiGeneSnpOutput(el,f,'\t','\n');
/* Print out bgiGeneSnp as a line in a tab-separated file. */

#define bgiGeneSnpCommaOut(el,f) bgiGeneSnpOutput(el,f,',',',');
/* Print out bgiGeneSnp as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* BGIGENESNP_H */

