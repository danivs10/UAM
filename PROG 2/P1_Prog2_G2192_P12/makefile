all: p1_e3 p1_e2 p1_e1

p1_e3: p1_e3.o node.o graph.o
	gcc p1_e3.o node.o graph.o -g -o p1_e3

p1_e2: p1_e2.o node.o graph.o
	gcc p1_e2.o node.o graph.o -g -o p1_e2

p1_e1: p1_e1.o node.o graph.o
	gcc p1_e1.o node.o graph.o -g -o p1_e1

graph.o: graph.c graph.h types.h
	gcc -ansi -pedantic -Wall -g -c graph.c

node.o: node.c node.h types.h
	gcc -ansi -pedantic -Wall -g -c node.c

p1_e3.o: p1_e3.c node.h graph.h types.h
	gcc -ansi -pedantic -Wall -g -c p1_e3.c

p1_e2.o: p1_e2.c node.h graph.h types.h
	gcc -ansi -pedantic -Wall -g -c p1_e2.c

p1_e1.o: p1_e1.c node.h types.h
	gcc -ansi -pedantic -Wall -g -c p1_e1.c

clean:
	rm -f *.o

clear:
	rm p1_e1
	rm p1_e2
	rm p1_e3
	rm test_p1_e1
	rm test_p1_e2

test1: test_p1_e1

test_p1_e1: test_p1_e1.o node.o
	gcc -g test_p1_e1.o node.o -o test_p1_e1

test_p1_e1.o: test_p1_e1.c
	gcc -c -ansi -pedantic -Wall -g test_p1_e1.c

test2: test_p1_e2

test_p1_e2: test_p1_e2.o node.o
	gcc -g test_p1_e2.o node.o graph.o -o test_p1_e2

test_p1_e2.o: test_p1_e2.c
	gcc -c -ansi -pedantic -Wall -g test_p1_e2.c