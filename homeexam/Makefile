CCFLAGS= -g

all: routing_server node

routing_server: header.h routing_server.c
	$(CCFLAGS) routing_server.c -o routing_server

node: node.c 

run: all
	bash run.sh

clean:
	rm -f routing_server
	rm -f node
