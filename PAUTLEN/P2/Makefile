all: pruebaMorfo

pruebaMorfo: lex.yy.o pruebaMorfo.o
	gcc -o pruebaMorfo lex.yy.o pruebaMorfo.o

pruebaMorfo.o:
	gcc -Wall -ansi -pedantic -c -o pruebaMorfo.o pruebaMorfo.c

lex.yy.o:
	flex alfa.l
	gcc -c -o lex.yy.o lex.yy.c

clean:
	rm -rf pruebaMorfo  *.o lex.yy.c