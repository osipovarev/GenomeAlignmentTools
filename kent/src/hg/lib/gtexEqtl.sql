# gtexEqtl.sql was originally generated by the autoSql program, which also 
# generated gtexEqtl.c and gtexEqtl.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#BED 9+ of expression Quantitative Trait Loci (eQTL). These are variants affecting gene expression
CREATE TABLE gtexEqtl (
    bin int unsigned not null,	# Bin number for browser speedup
    chrom varchar(255) not null,	# Reference sequence chromosome or scaffold
    chromStart int unsigned not null,	# Start position in chromosome
    chromEnd int unsigned not null,	# End position in chromosome
    name varchar(255) not null,	# Variant/gene pair
    score int unsigned not null,	# Score from 0-1000 (highest probabiliity in cluster * 1000)
    strand char(1) not null,	# .
    thickStart int unsigned not null,	# Start position
    thickEnd int unsigned not null,	# End position
    reserved int unsigned not null,	# R,G,B color: red +effect, blue -effect. Bright for high, pale for lower (cutoff effectSize 2.0 RPKM).
    variant varchar(255) not null,	# Variant (rsID or GTEx identifier if none)
    geneId varchar(255) not null,	# Target gene identifier
    gene varchar(255) not null,	# Target gene symbol
    distance int not null,	# Distance from TSS
    effectSize float not null,	# Effect size (FPKM)
    pValue float not null,	# Nominal p-value
    causalProb float not null,	# Probability variant is in high confidence causal set
              #Indices
    INDEX (chrom,bin),
    INDEX (geneId),
    INDEX (gene),
    INDEX (variant),
    PRIMARY KEY (geneId,variant)
);
