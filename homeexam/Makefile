CC=gcc
CFLAGS= -Wall -Wextra -Wpedantic -std=c99 -g

all: routing_server node

routing_server: header.h routing_server.c
	$(CC) $(CFLAGS) routing_server.c -o routing_server

node: node.c
	$(CC) $(CFLAGS) node.c -o node

run: all
	bash run_1.sh 1024
	bash run_2.sh 2345

clean:
	rm -f routing_server
	rm -f node
