CFLAGS = -ansi -pedantic -g

all: lex.yy.o y.tab.o pruebaSintactico.o
	gcc $(CFLAGS) -o pruebaSintactico lex.yy.o y.tab.o pruebaSintactico.o

pruebaSintactico.o: y.tab.h pruebaSintactico.c
	gcc $(CFLAGS) -c pruebaSintactico.c

lex.yy.c: alfa.l
	$ flex alfa.l

lex.yy.o: lex.yy.c y.tab.h
	gcc $(CFLAGS) -c -o lex.yy.o lex.yy.c

y.tab.h: alfa.y
	$ bison -d -y -v alfa.y
	
y.tab.o: y.tab.c
	gcc $(CFLAGS) -c -o y.tab.o y.tab.c


clean:
	rm -rf pruebaSintactico  *.o lex.yy.c y.tab.c *.h y.output