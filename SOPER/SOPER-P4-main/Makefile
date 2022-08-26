all: miner monitor

monitor: monitor.o common.o
	gcc monitor.o common.o -o monitor -lrt -lpthread

monitor.o: monitor.c
	gcc -c monitor.c -g

miner: miner.o common.o
	gcc miner.o common.o -o miner -lpthread -lrt

miner.o: miner.c
	gcc -c miner.c -g

common: common.o
	gcc common.o -o common -lpthread -lrt

common.o: common.c
	gcc -c common.c

clean:
	rm miner monitor *.o