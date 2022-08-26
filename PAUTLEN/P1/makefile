all: ej1 ej2 ej3 ej4 ej5 ej6 ej7

ej1:
	gcc -Wall -g -o ej1_ex generacion.c ej1.c
	./ej1_ex ej1.asm
	nasm -g -o ej1.o -f elf32 ej1.asm
	gcc -Wall -g -m32 -o ej1 ej1.o alfalib.o

ej2:
	gcc -Wall -g -o ej2_ex generacion.c ej2.c
	./ej2_ex ej2.asm
	nasm -g -o ej2.o -f elf32 ej2.asm
	gcc -Wall -g -m32 -o ej2 ej2.o alfalib.o

ej3:
	gcc -Wall -g -o ej3_ex generacion.c ej3.c
	./ej3_ex ej3.asm
	nasm -g -o ej3.o -f elf32 ej3.asm
	gcc -Wall -g -m32 -o ej3 ej3.o alfalib.o

ej4:
	gcc -Wall -g -o ej4_ex generacion.c ej4.c
	./ej4_ex ej4.asm
	nasm -g -o ej4.o -f elf32 ej4.asm
	gcc -Wall -g -m32 -o ej4 ej4.o alfalib.o

ej5:
	gcc -Wall -g -o ej5_ex generacion.c ej5.c
	./ej5_ex ej5.asm
	nasm -g -o ej5.o -f elf32 ej5.asm
	gcc -Wall -g -m32 -o ej5 ej5.o alfalib.o

ej6:
	gcc -Wall -g -o ej6_ex generacion.c ej6.c
	./ej6_ex ej6.asm
	nasm -g -o ej6.o -f elf32 ej6.asm
	gcc -Wall -g -m32 -o ej6 ej6.o alfalib.o

ej7:
	gcc -Wall -g -o ej7_ex generacion.c ej7.c
	./ej7_ex ej7.asm
	nasm -g -o ej7.o -f elf32 ej7.asm
	gcc -Wall -g -m32 -o ej7 ej7.o alfalib.o

clear:
	rm *.asm
	rm *_ex
	mv alfalib.o alfalib
	rm *.o
	mv alfalib alfalib.o