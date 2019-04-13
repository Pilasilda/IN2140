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

//Max number of bytes node 1 can get at once
#define MAXDATASIZE 100
#define INFINITY 9999
#define SERVER_PORT 1024
#define BACKLOG 32
#define MAX_NEIGHBOURS 20
#define Respons "Connection accpted! Thank you!\n"

struct node{
  int id;
  int number_of_nodes;
  int sock;
  struct node* nodes[MAX_NEIGHBOURS];
};

struct neighbour{
  int id;
  int weight;
};

char buffer[MAXDATASIZE];

//Methods
void run_server(int);
int create_socket();
int tcp_socket_client();
struct neighbour* add_neighbour(char*);
int create_tcpsocket();
void edge_info(int, int, struct neighbour**);
//int dijsktra(int, int , int);

#endif
