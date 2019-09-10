# ucscRetroOrtho.sql was originally generated by the autoSql program, which also 
# generated ucscRetroOrtho.c and ucscRetroOrtho.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Orthlogy of retrogenes based on chains/nets with other species.
CREATE TABLE ucscRetroOrtho1 (
    name varchar(255) not null,	# Unique name of retrogene 
    db varchar(255) not null,	# database of other species
    overlap int not null,	# percent of retro that breaks net relative to other species
              #Indices
    PRIMARY KEY(name,db)
);
