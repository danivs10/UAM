CC = gcc
CFLAGS = -Wall -Wextra -pedantic -ansi
LDLIBS = -lodbc

EXE = menu   

export PGDATABASE:=classicmodels
export PGUSER :=alumnodb
export PGPASSWORD :=alumnodb
export PGCLIENTENCODING:=LATIN9
export PGHOST:=localhost



DBNAME =$(PGDATABASE)
PSQL = psql
CREATEDB = createdb
DROPDB = dropdb --if-exists
PG_DUMP = pg_dump
PG_RESTORE = pg_restore

all : clean dropdb createdb restore 

errors:
	splint -nullpass *.c *.h > splint.log

compile:$(EXE) errors

clean :
	rm -f *.o core $(EXE)

$(EXE) : % : %.o odbc.o products.o orders.o customers.o


createdb:
	@echo Creando BBDD
	@$(CREATEDB)
dropdb:
	@echo Eliminando BBDD
	@$(DROPDB) $(DBNAME)
	rm -f *.log
dump:
	@echo creando dumpfile
	@$(PG_DUMP) > $(DBNAME).sql
restore:
	@echo restore data base
	@cat $(DBNAME).sql | $(PSQL)  
