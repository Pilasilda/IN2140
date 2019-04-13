#include "header.h"

int main(int argc, char* argv[]){
  struct neighbour** nodene;
  int id,tcp_socket;
  long baseport;
  int j=0;
  char *div;

  if(argc < 2){
    exit(EXIT_FAILURE);
  }
  /*
  ** reading 1 and 2 arugment
  */
  baseport = atoi(argv[1]);
  printf("Port: %ld\n", baseport);
  id = atoi(argv[2]);


  for(j = 3; j < argc; j++){
    nodene = malloc(sizeof(struct neighbour*)*j);
    div = argv[j];
    nodene[j] = add_neighbour(div);
  }
  //}

  //Setting up socket connection
  printf("Setting up connection socket\n");

  /*
  if(tcp_socket == 0){
    exit(EXIT_FAILURE);
  }*/

  tcp_socket = tcp_socket_client(baseport);
  edge_info(id, j, nodene);

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


int tcp_socket_client(long port){
  int tcp_socketclient;
  int counter=1;
  struct sockaddr_in socket_address;
  socklen_t client;

  if((tcp_socketclient = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    printf("\n Error during creating socket\n");
    return -1;
  }

  setsockopt(tcp_socketclient, SOL_SOCKET, SO_REUSEADDR,&counter, sizeof(int));
  socket_address.sin_family = AF_INET;
  socket_address.sin_port = htons(port);
  socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
  /*
  ** Coonect socket to server using struct
  */
  client = sizeof(socket_address);
  connect(tcp_socketclient, (struct sockaddr*)&socket_address, client);
  /*
  **print received message
  */
  //printf("Data received:%s \n",buffer);
  return tcp_socketclient;
}

/*
** method which malloc struct neighbour, used for reading arguments
*/
struct neighbour* add_neighbour(char* n){
  struct neighbour* pointer;

  pointer = malloc(sizeof(struct neighbour));
  pointer->id = (int)atoi(strtok(n, ":"));
  pointer->weight = (int)atoi(strtok(NULL,""));
  return pointer;
}
/*
**sends edge information to server
*/
void edge_info(int adress,int num,struct neighbour** neighbour){
  int i;
  char msg[MAXDATASIZE];

  sprintf(msg, "Node id: %d\n", adress);
  printf("%s", msg);

  sprintf(msg, "Neighbour: %s %d\n",msg, num);
  printf("%s",msg);

  for(i = 0; i < num; i++){
    sprintf(msg, "%s %d %d", msg, neighbour[i]->id, neighbour[i]->weight);
  }
  printf("%s\n", msg);
}
