EX1=p4_e1
EX2=p4_e2
EX3a=p4_e3_b
EX3b=p4_e3_b

CFLAGS = -g -Wall -ansi -pedantic

all:$(EX1) $(EX2) $(EX3a) $(EX3b)

$(EX1): p4_e1.o libstack_fp.a liblist.a
	gcc p4_e1.o libstack_fp.a liblist.a -o $(EX1)

$(EX2): queue_fp.o node.o graph_list.o p4_e2.o liblist.a
	gcc p4_e2.o queue_fp.o node.o graph_list.o liblist.a -o $(EX2)

$(EX3a): p4_e3_a.o queue_fp.o node.o graph_list.o liblist.a tree.o
	gcc p4_e3_a.o tree.o node.o graph_list.o liblist.a -o $(EX3a)

$(EX3b): p4_e3_b.o queue_fp.o node.o graph_list.o liblist.a tree.o libstack_fp.a
	gcc p4_e3_b.o tree.o node.o graph_list.o liblist.a -o $(EX3a)

p4_e1.o: p4_e1.c stack_fp.h stack_types.h list.h types.h
	gcc $(CFLAGS) -c p4_e1.c

p4_e2.o: p4_e2.c queue_fp.h node.h graph_list.h types.h list.h
	gcc $(CFLAGS) -c p4_e2.c

p4_e3_a.o: p4_e3_a.c queue_fp.h node.h graph_list.h types.h list.h 
	gcc $(CFLAGS) -c p4_e3_a.c

p4_e3_b.o: p4_e3_b.c queue_fp.h stack_types.h graph_list.h types.h list.h 
	gcc $(CFLAGS) -c p4_e3_b.c

graph_list.o: graph_list.c graph_list.h types.h
	gcc $(CFLAGS) -c graph_list.c

clean:
	rm -f *o

clear:
	rm p4_e1
	rm p4_e2
	rm p4_e3_a