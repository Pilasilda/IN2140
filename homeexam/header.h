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

int N = 0;

struct nabo{
  int edge;
  int node;
  struct node *nabo[MAX_NEIGHBOURS];
};

struct node{
  int id;
  int vekt;
};


char buffer[MAXDATASIZE];

//Methods
void run_server(int);
int create_socket();
int connect_socket();
int create_tcpsocket();
int edge_info(int, int);
//int dijsktra(int, int , int);

#endif
