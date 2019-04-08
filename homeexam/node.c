#include "header.h"
int tcp_socketclient;
struct sockaddr_in socket_address = {0};
struct node **naboene;
naboene = malloc(sizeof(struct node));
socklen_t client;


struct nabo{
  int egde;
  int node;
};

struct node{
  int id;
};

int main(int argc, char* argv[]){
  int connect,check,j,a;
  char* i;
  connect = connect_socket();

  /*
  **node information
  */
  check = edge_info(argv[2]);

  /*
  ** number of arguments
  */
  if(argc > 0){
    j  = argc-3;
    return 0;
  }

  edge_info(argv[j]);


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
  socket_address.sin_postruct ruter **rutere;rt = htons(SERVER_PORT);
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
int edge_info(char *adress, int num){
  int i;
  /*
  ** Value of node
  */
  char msg[MAXDATASIZE];
  sprintf(msg, "Node id:%d\n", adress);
  printf("%s",msg);
  /*
  ** Neighbour of node
  */
  sprintf(msg, "Neighbour:%s%d\n",msg, num);
  //printf("%s",msg);
  for(i = 0; i < num; i++){
    sprintf(msg, "%s %d %d", msg, naboene[i]->id);
  }
}
