# protVar.sql was originally generated by the autoSql program, which also 
# generated protVar.c and protVar.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#track for mutation data
CREATE TABLE protVar (
    id varchar(50) not null,	# unique ID for this mutation
    name varchar(255) not null,	# Official nomenclature description of mutation
    srcId varchar(255) not null,	# source ID for this mutation
    baseChangeType varchar(255) not null,	# enum('insertion', 'deletion', 'substitution','duplication','complex','unknown')
    location varchar(255) not null,	# enum('intron', 'exon', '5'' UTR', '3'' UTR', 'not within known transcription unit')
    coordinateAccuracy tinyint unsigned not null,	# 0=estimated, 1=definite, others?
              #Indices
    PRIMARY KEY(id)
);

#location of mutation
CREATE TABLE protVarPos (
    bin smallint unsigned not null,	# A field to speed indexing
    chrom varchar(255) not null,	# Chromosome
    chromStart int unsigned not null,	# Start position in chrom
    chromEnd int unsigned not null,	# End position in chrom
    name varchar(255) not null,	# ID for this mutation
    strand char(1) not null,	# + or -
    label varchar(255) not null,	# short official name for this mutation
              #Indices
    INDEX(bin)
);

#attributes asssociated with the mutation
CREATE TABLE protVarAttr (
    id varchar(50) not null,	# mutation ID
    attrType varchar(255) not null,	# attribute type
    attrVal longblob not null,	# value for this attribute
              #Indices
    INDEX(id, attrType)
);

#links both urls and local table lookups
CREATE TABLE protVarLink (
    id varchar(50) not null,	# id for attribute link
    attrType varchar(255) not null,	# attribute type
    raKey varchar(255) not null,	# key into .ra file on how to do link
    acc varchar(255) not null,	# accession or id used by link
    displayVal varchar(255) not null,	# value to display if different from acc
              #Indices
    INDEX(id, attrType)
);
