# arcogdesc.sql was originally generated by the autoSql program, which also 
# generated arcogdesc.c and arcogdesc.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#arCOG Description
CREATE TABLE arcogdesc (
    name varchar(255) not null,	# arCOG name
    code char(1) not null,	# COG Code
    description varchar(255) not null,	# arCOG description
              #Indices
    PRIMARY KEY(name)
);
