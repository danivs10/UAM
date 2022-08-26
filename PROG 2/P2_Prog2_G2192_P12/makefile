EX1=p2_e0_a
EX2=p2_e0_b
EX3=p2_e1
EX4=p2_e2
EX5=p2_e3_a
EX6=p2_e3_b

CFLAGS = -g -Wall -ansi -pedantic

all:$(EX1) $(EX2) $(EX3) $(EX4) $(EX5) $(EX6)

$(EX1): p2_e0_a.o libstack_fp.a
	gcc p2_e0_a.o libstack_fp.a -o $(EX1)

p2_e0_a.o: p2_e0_a.c stack_fp.h types.h
	gcc $(CFLAGS) -c p2_e0_a.c

$(EX2): p2_e0_b.o node.o libstack_fp.a
	gcc p2_e0_b.o node.o libstack_fp.a -o $(EX2)

p2_e0_b.o: p2_e0_b.c stack_fp.h node.h types.h
	gcc $(CFLAGS) -c p2_e0_b.c


node.o: node.c node.h types.h
	gcc $(CFLAGS) -c node.c

$(EX3): p2_e1.o libstack_fp.a
	gcc p2_e1.o libstack_fp.a -o $(EX3)

p2_e1.o: p2_e1.c stack_fp.h types.h
	gcc $(CFLAGS) -c p2_e1.c

$(EX4): p2_e2.o libstack_fp.a
	gcc p2_e2.o libstack_fp.a -o $(EX4)

p2_e2.o: p2_e2.c stack_fp.h types.h
	gcc $(CFLAGS) -c p2_e2.c

$(EX5): p2_e3_a.o element.o stack.o
	gcc p2_e3_a.o element.o stack.o -o $(EX5)

p2_e3_a.o: p2_e3_a.c stack.h types.h
	gcc $(CFLAGS) -c p2_e3_a.c

$(EX6): p2_e3_b.o element.o stack.o
	gcc p2_e3_b.o element.o stack.o -o $(EX6)

p2_e3_b.o: p2_e3_b.c stack.h types.h
	gcc $(CFLAGS) -c p2_e3_b.c

element.o: element.c element.h types.h
	gcc $(CFLAGS) -c element.c

stack.o: stack.c stack.h element.h types.h
	gcc $(CFLAGS) -c stack.c

clean:
	rm -f *o

clear:
	rm p2_e0_a 
	rm p2_e0_b 
	rm p2_e1
	rm p2_e2
	rm p2_e3_a
	rm p2_e3_b