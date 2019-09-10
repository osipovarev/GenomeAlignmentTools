# genotypeFreqs.sql was originally generated by the autoSql program, which also 
# generated genotypeFreqs.c and genotypeFreqs.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Genotype Frequencies from HapMap
CREATE TABLE genotypeFreqs (
    rsId varchar(255) not null,	# rs		rs2104604
    chrom varchar(255) not null,	# chrom		Chr1
    chromStart int not null,	# pos		101809619
    strand char(1) not null,	# strand		+
    assembly varchar(255) not null,	# build		ncbi_34
    center varchar(255) not null,	# center		bcm
    protLSID varchar(255) not null,	# protLSID
    assayLSID varchar(255) not null,	# assayLSID
    panelLSID varchar(255) not null,	# panelLSID
    majGt varchar(255) not null,	# majorhom-gt	G/G
    majFreq float not null,	# majorhom-freq	1
    majCount int not null,	# majorhom-count	60
    hetGt varchar(255) not null,	# het-gt		G/T
    hetFreq float not null,	# het-freq	0
    hetCount int not null,	# het-count	0
    minGt varchar(255) not null,	# minorhom-gt	T/T
    minFreq float not null,	# minorhom-freq	0
    minCount int not null,	# minorhom-count	0
    totCount int not null,	# totalcount	60
    minAlFreq float not null,	# maf		0
              #Indices
    INDEX(rsId)
);
