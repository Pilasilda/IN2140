#include "header.h"
int tcp_socketclient;
struct node **nodene;
struct sockaddr_in socket_address;
socklen_t client;

int main(int argc, char* argv[]){
  int port, edges,tcp_socket;
  int j = 0;
  port = atoi(argv[1]);
  printf("Port:% d\n",  port);
  edges = atoi(argv[2]);
  printf("Node id: %d\n", edges);
  char* neighbour = argv [3];

  //finding neighbours og edges
  int size = sizeof(neighbour);
  char div [] = ":";
  char* str = strtok(neighbour,div);

  while(str != NULL){
    printf("%d\n",str);
    str = strtok(NULL, div);
    printf("Naboer: %d%c%d",port, div,edges);
  }

  //Setting up socket connection
  printf("Setting up connection socket\n");
  tcp_socket = connect_socket();

  if(tcp_socket == 0){
    exit(EXIT_FAILURE);
  }
  /*
  **number of arguments
  */
  //tcp_socket = edge_info(port, edges);
  //fprintf(stderr,"%d\n", tcp_socket);

  /*
  for(j = 3; j < argc; j++){
    printf("Arguments%s\n", argv[j]);
  }*/


  /*1. Finne antall noder
  2. Først send adresse av node
  3. antall_ naboer finner: dette gjort i argc
  4. Går gjennom melding */



  /*
  1. FINNE ANTALL NODER1
  2. SPRINTF: FØRST SEND MED ADRESSE TIL Node
  3. SPRINTF: antall nabo finner det ved argc-3
  4. sprint: forløkke som går gjennom melding legger til melding
  5. If test som sjekker om riktig antall melding blir sendt
  */
}


int connect_socket(){
  if((tcp_socketclient = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("\n Error during creating socket\n");
    return -1;
  }

  socket_address.sin_family = AF_INET;
  socket_address.sin_port = htons(SERVER_PORT);
  socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
  /*
  ** Coonect socket to server using struct
  */
  client = sizeof(socket_address);
  connect(tcp_socketclient, (struct sockaddr*)&socket_address, client);
  /*
  **read message from server into buffer
  */
  recv(tcp_socketclient, buffer, sizeof(buffer), 0);
  /*
  **print received message
  */
  //printf("Data received:%s \n",buffer);
  close(tcp_socketclient);
  return 0;
}

/*
**sends edge information to server
*/
int edge_info(int adress, int num){
  nodene  = malloc(sizeof(struct node*));
  //int i;
  char msg[MAXDATASIZE];

  sprintf(msg, "Node id: %d\n", adress);
  sprintf(msg, "Neighbour: %s %d\n",msg, num);

  /*
  for(i = 0; i < num; i++){
    sprintf(msg, "%s %d %d", msg, nodene[i]->id, nodene[i]->vekt);
  }*/
  //printf("%s\n", msg);

  return 1;
}
