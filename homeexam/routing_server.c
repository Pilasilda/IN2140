#include "header.h"
struct sockaddr_in server_address;
int len = sizeof(server_address);
socklen_t client;
int tcp_socket;

int main(int argc, char *argv[]){
  int tcp_socket;

  tcp_socket = create_tcpsocket();

  int g[MAX_NEIGHBOURS][MAX_NEIGHBOURS] = {{0,2,6,INFINITY,INFINITY,INFINITY,INFINITY,INFINITY},
                                               {2,0,INFINITY,2,INFINITY,7,INFINITY,INFINITY},
                                               {6,INFINITY,0,1,INFINITY,INFINITY,INFINITY,4},
                                               {INFINITY,2,1,0,2,INFINITY,INFINITY,INFINITY},
                                               {INFINITY,INFINITY,INFINITY,2,0,4,INFINITY,2},
                                               {INFINITY,7,INFINITY,INFINITY,4,0,3,INFINITY},
                                               {INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,3,0,2},
                                               {INFINITY,INFINITY,4,INFINITY,2,INFINITY,2,0}};
   dijsktra(g, 8,1);




}

/*
** method for creating tcp socket for server
*/
int create_tcpsocket(){
  int counter = 1;
  int var,tcp_socket_server;

  printf("Creating TCP server socket\n");
  /*creating the socket and verfication  */
  tcp_socket_server = socket(AF_INET, SOCK_STREAM, 0);
  if(tcp_socket_server == -1){
    printf("Failed creating the socket()\n");
    exit(1);
  }

  //printf("TCP socket created \n");
  /*Specifying connection and port, assign ip and port*/
  /*possible to reuse port after previous user*/
  setsockopt(tcp_socket_server, SOL_SOCKET, SO_REUSEADDR,&counter, sizeof(int));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(SERVER_PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  /*Binding to adress*/
  printf("Binding server socket to port %d \n", SERVER_PORT);
  if(bind(tcp_socket_server, (struct sockaddr*) &server_address, sizeof(server_address)) < 0){
    perror("Failed using bind()");
    exit(EXIT_FAILURE);
  }
  //printf("Socket successfully bound\n");
  //printf("Trying to listen to socket....\n");

  var = listen(tcp_socket_server, BACKLOG);
  if(var == -1){
    printf("Failed listning");
    exit(EXIT_FAILURE);
  }
  run_server(tcp_socket_server);

  return tcp_socket;
}

/*server for max number of clients/nodes*/
void run_server(int socket){
  struct sockaddr_in client_addr;
  socklen_t addrlen = sizeof(struct sockaddr_in);
  char buffer[16];

  while(1){
    int i;
    i = accept(socket,(struct sockaddr*) &client_addr, &addrlen);
    if(i == -1){
      printf("Accept() failed");
      perror("accept");
      break;
    }

    if(!inet_ntop(client_addr.sin_family,&(client_addr.sin_addr),buffer,addrlen)){
      printf("Error!\n");
      perror("inet_ntop");
      strcpy(buffer, "N/A");
    }
    printf("Connection %s and port %u\n",buffer,ntohs(client_addr.sin_port));
    write(i, Respons, strlen(Respons));
    readMessage(socket);
    close(i);
  }
}

void handleMessage(int tcp_socket_client,fd_set *fds){
  int i;
  ssize_t nr_bytes;
  char* recv_message;


}

void dijsktra(int graph[MAX_NEIGHBOURS][MAX_NEIGHBOURS], int n, int start_node){
  /*distance from node to node*/
  int cost[MAX_NEIGHBOURS][MAX_NEIGHBOURS];
  /*distance from predecessors to source node*/
  int distance[MAX_NEIGHBOURS];
  /*stores predecessors that are visited nodes */
  int pred[MAX_NEIGHBOURS];
  /*store if node has been visited*/
  bool visited[MAX_NEIGHBOURS];

  int count, mindistance,i, j;
  int visit_next = 0;

  for(i=0; i < n; i++){
    for(j=0; j < n; j++){
      if(graph[i][j] == 0){
        cost[i][j] = INFINITY;
      }else{
        cost[i][j] = graph[i][j];
      }
    }
  }

  for(i = 0; i < n; i++){
    distance[i] = cost[start_node][i];
    pred[i] = start_node;
    visited[i] = false;
  }

  distance[start_node] = 0;
  visited[start_node] = true;
  count = 1;

  while(count < n - 1){
    mindistance = INFINITY;

    for(i = 0; i < n; i++)
      if(distance[i] < mindistance && !visited[i]){
        mindistance = distance[i];
        visit_next = i;
      }

    visited[visit_next] = true;

    for(i = 0; i < n; i++)
      if(!visited[i])
        if(mindistance+cost[visit_next][i] < distance[i]){
          distance[i] = mindistance+cost[visit_next][i];
          pred[i] = visit_next;
        }
      count++;
    }

    for(i = 0; i < n; i++)
      if(i != start_node){
        printf("\nDistance of node %d->%d\n",i,distance[i]);
        printf("\nPath=%d\n",i);
        j = i;
        do{
          j = pred[j];
          printf("<-%d",j);
        }while(j != start_node);
      }
}



int reported(){
  struct node* node = {0};
  struct neighbour* neighbour = {0};
  int i;

  for(i=0; i < number_of_nodes;i++){
    if(neighbour[i].weight == neighbour[i].weight){
      printf("Edges beteween node and neighbour node are same.\n");
      return 1;
    }else{
      printf("Edges are not same.\n");
      exit(0);
    }
  }
  /*
  1. Hver kant har blitt rapportert to ganger
      - En gang hver begge nodene, kant mellom node har samme vekt
      - En gang for at begge nodene har samme vekt
  2. Hvis ikke, skrive advarsel og ignorere kant.
  */
  return 1;
}
