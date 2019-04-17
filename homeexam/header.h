#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netdb.h>
#include "print_lib.h"
#include <stdbool.h>

//Max number of bytes node 1 can get at once
#define MAXDATASIZE 100
#define INFINITY 9999
#define INFINITY 9999
#define SERVER_PORT 1024 //the port users will be connecting to
#define BACKLOG 32 //how many connections queue will hold
#define MAX_NEIGHBOURS 20 //max number of neighbournodes a node can have
#define Respons "Connection accpted! Thank you!\n"

int number_of_nodes;

struct node{
  int id;
  int nr_connections;
  struct node* connection[MAX_NEIGHBOURS];
};

struct neighbour{
  int id;
  int weight;
};

struct nr_of_bytes{
  uint32_t file_size;
  uint8_t file;
  char* file_name;
}

char buffer[MAXDATASIZE];

//Methods
void run_server(int);
int create_socket();
void readMessage();
int tcp_socket_client(int);
struct neighbour* add_neighbour(char*);
int create_tcpsocket();
void edge_info(int, int, struct neighbour**,int);
void dijsktra(int graph[MAX_NEIGHBOURS][MAX_NEIGHBOURS],int,int);
int reported();


#endif
