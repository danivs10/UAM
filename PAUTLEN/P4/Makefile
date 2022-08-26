CFLAGS = -ansi -pedantic -g

all: hashTable.o tablaSimbolos.o
	gcc $(CFLAGS) -o tablaSimbolos hashTable.o tablaSimbolos.o

tablaSimbolos.o: tablaSimbolos.c 
	gcc $(CFLAGS) -c tablaSimbolos.c

hashTable.o: hashTable.c
	gcc $(CFLAGS) -c hashTable.c
	
clean:
	rm *.o tablaSimbolos
