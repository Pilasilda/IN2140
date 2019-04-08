#include "header.h"
struct sockaddr_in server_address;
struct sockaddr_storage storage;

socklen_t client;
int tcp_socket;

int main(int argc, char *argv[]){
  int tcp_socket;

  tcp_socket = create_tcpsocket();
}

/*
** method for creating tcp socket
*/
int create_tcpsocket(){
  int counter;
  int accepted;
  int var;
  /*
  ** Message on terminal creating socket
  */
  printf("Create server socket \n");
  /*
  ** creating the socket and verfication
  */
  tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

  if(tcp_socket == -1){
    printf("Failed creating the socket()");
    perror("socket");
    exit(0);
  }
  /*
  ** Message to terminal socket created
  */
  printf("Socket created \n");
  /*
  **  Specifying connection and port, assign ip and port
  */
  server_address.sin_family = AF_INET; //adress for IPv4
  server_address.sin_port = htons(SERVER_PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;
  /*
  ** possible to reuse port after previous user
  */
  setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR,&counter, sizeof(int));
  printf("Binding server socket to port %d \n", SERVER_PORT);
  var = bind(tcp_socket, (struct sockaddr*) &server_address, sizeof(server_address));

  if(var){
    printf("Failed using bind()");
    perror("bind");
    exit(0);
  }

  printf("Successfully bound\n");
  printf("Trying to listen to socket....\n");

  var = listen(tcp_socket, BACKLOG);
  if(var == -1){
    printf("Failed listning");
    perror("Listning\n");
    exit(0);
  }

  printf("Listning to socket now\n");

  client = sizeof(storage);
  accepted = accept(tcp_socket, (struct sockaddr*) &storage, &client);

  if(accepted < 0){
    printf("Server accept failed\n");
    perror("accepted");
  }else{
    printf("Server accepted client\n");
  }

  //strcpy(buffer, "Hello world\n");
  send(accepted,buffer,sizeof(server_address),0);

  return 0;
}


/*
int dijsktra(int cost[antall][antall], int n, int start){
  int graf[antall][antall];
  int distance[antall];
  int pred[antall];
  int visited[antall];
  //count: antall noder som er "sett"
  int count, mindistance, next, i, j;

  for(i=0; i < n; i++){
    for(j=0; j < n; j++){
      if(graf[i][j] == 0){
        cost[i][j] = INFINITY;
      }else{
        cost[i][j] = graf[i][j];
      }
    }
  }

  for(i = 0; i < n; i++){
    distance[i] = cost[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  distance[start] = 0;
  visited[start] = 1;
  count = 1;

  while(count < n - 1){
    mindistance = INFINITY;

    for(i = 0; i < n; i++)
      if(distance[i] < mindistance&&!visited[i]){
        mindistance=distance[i];
        next = i;
      }

        visited[next] = 1;
        for(i =0; i < n; i++)
          if(!visited[i])
            if(mindistance+cost[next][i]< distance[i]){
              distance[i] = mindistance+cost[next][i];
              pred[i] = next;
            }
            count++;
    }

    for(i = 0; i < n; i++)
      if(i!= start){
        printf("\nDistance of node %d->%d",i,distance[i]);
        printf("\nPath=%d",i);
        j = i;
        do{
          j = pred[j];
          printf("<-%d",j);
        }while(j!=start);
      }
      return 0;
}

int main(int argc, char* argv[]){
  if(argc < 1){
    return 0;
  }
  dijsktra(argv[1],argv[2],argv[3]);
}*/
