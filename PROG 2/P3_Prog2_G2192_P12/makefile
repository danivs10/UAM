EX1=p3_e1
EX2=p3_e2
EX3=p3_e3
EX4=p3_e3_c
CFLAGS = -g -Wall -ansi -pedantic -c
LFLAGS = -o

all:$(EX1) $(EX2) $(EX3) $(EX4)

$(EX1): queue_fp.o node.o graph.o p3_e1.o
	gcc -g p3_e1.o queue_fp.o node.o graph.o $(LFLAGS) $(EX1)

$(EX2): queue_fp.o node.o graph.o p3_e2.o
	gcc -g queue_fp.o node.o graph.o p3_e2.o $(LFLAGS) $(EX2)

$(EX3): queue_fp.o node.o graph.o p3_e3.o libstack_fp.a
	gcc -g queue_fp.o node.o graph.o p3_e3.o libstack_fp.a $(LFLAGS) $(EX3)

$(EX4): queue_fp.o node.o graph.o p3_e3_c.o libstack_fp.a
	gcc -g queue_fp.o node.o graph.o p3_e3_c.o libstack_fp.a $(LFLAGS) $(EX4)

queue_fp.o: queue_fp.c queue_fp.h types.h
	gcc $(CFLAGS) queue_fp.c 

node.o: node.c node.h types.h
	gcc $(CFLAGS) node.c

graph.o: graph.c node.h graph.h types.h
	gcc $(CFLAGS) graph.c
	
p3_e1.o: p3_e1.c queue_fp.h node.h graph.h types.h
	gcc $(CFLAGS) p3_e1.c 

p3_e2.o: p3_e2.c queue_fp.h node.h graph.h types.h
	gcc $(CFLAGS) p3_e2.c

p3_e3.o: p3_e3.c queue_fp.h stack_fp.h node.h graph.h types.h
	gcc $(CFLAGS) p3_e3.c

clean:
	rm -f *o

clear:
	rm p3_e1
	rm p3_e2
	rm p3_e3
	rm p3_e3_c