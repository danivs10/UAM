CFLAGS = -ansi -pedantic -g
OBJECTS =  lex.yy.o y.tab.o main.o hashTable.o generacion.o tablaSimbolos.o 


all: $(OBJECTS)
	gcc $(CFLAGS) -o alfa $(OBJECTS)

tablaSimbolos.o: tablaSimbolos.c tablaSimbolos.h
	gcc $(CFLAGS) -c tablaSimbolos.c

hashTable.o: hashTable.c hashTable.h
	gcc $(CFLAGS) -c hashTable.c

generacion.o: generacion.c generacion.h
	gcc $(CFLAGS) -c generacion.c

main.o: main.c y.tab.c
	gcc $(CFLAGS) -c main.c

lex.yy.o: lex.yy.c y.tab.c alfa.h
	gcc $(CFLAGS) -c lex.yy.c

y.tab.o: y.tab.c 
	gcc $(CFLAGS) -c y.tab.c

lex.yy.c: alfa.l y.tab.c
	flex alfa.l

y.tab.c: alfa.y 
	bison -d -y -v alfa.y
	
ejemplo_1:
	./alfa ejemplo_condicionales/condicionales.alfa ejemplo_condicionales/nuestro_resultado.asm
	nasm -felf32 ejemplo_condicionales/nuestro_resultado.asm
	gcc -m32 -o ejemplo_condicionales/nuestro_resultado ejemplo_condicionales/nuestro_resultado.o alfalib.o

ejemplo_2:
	./alfa ejemplo_factorial/factorial.alfa ejemplo_factorial/nuestro_resultado1.asm
	nasm -felf32 ejemplo_factorial/nuestro_resultado1.asm
	gcc -m32 -o ejemplo_factorial/nuestro_resultado1 ejemplo_factorial/nuestro_resultado1.o alfalib.o

ejemplo_3:
	./alfa ejemplo_fibonacci/fibonacci.alfa ejemplo_fibonacci/nuestro_resultado2.asm
	nasm -felf32 ejemplo_fibonacci/nuestro_resultado2.asm
	gcc -m32 -o ejemplo_fibonacci/nuestro_resultado2 ejemplo_fibonacci/nuestro_resultado2.o alfalib.o

ejemplo_4:
	./alfa ejemplo_funciones/funciones.alfa ejemplo_funciones/nuestro_resultado3.asm
	nasm -felf32 ejemplo_funciones/nuestro_resultado3.asm
	gcc -m32 -o ejemplo_funciones/nuestro_resultado3 ejemplo_funciones/nuestro_resultado3.o alfalib.o

ejemplo_5:
	./alfa ejemplo_funciones_vectores/funciones_vectores.alfa ejemplo_funciones_vectores/nuestro_resultado4.asm
	nasm -felf32 ejemplo_funciones_vectores/nuestro_resultado4.asm
	gcc -m32 -o ejemplo_funciones_vectores/nuestro_resultado4 ejemplo_funciones_vectores/nuestro_resultado4.o alfalib.o

ejemplo_a:
	./alfa ejemplo_logica/logica.alfa ejemplo_logica/nuestro_resultado5.asm
	nasm -felf32 ejemplo_logica/nuestro_resultado5.asm
	gcc -m32 -o ejemplo_logica/nuestro_resultado5 ejemplo_logica/nuestro_resultado5.o alfalib.o

ejhola:
	./alfa ejemplo_divisiones/hola.alfa ejemplo_divisiones/hola.asm
	nasm -felf32 ejemplo_divisiones/hola.asm
	gcc -m32 -o ejemplo_divisiones/hola ejemplo_divisiones/hola.o alfalib.o

clean:
	rm *.o -v !("alfalib.o")
