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


char buffer[MAXDATASIZE];

//Methods
int create_socket();
int create_tcpsocket();
int edge_info(char*);
//int dijsktra(int, int , int);

#endif
