#include "header.h"

int main(int argc, char* argv[]){
  struct neighbour** nodene = {0};
  int id,tcp_socket;
  int number_of_nodes;
  number_of_nodes = argc-3;
  long baseport;
  int j=0;
  char *div;

  if(argc < 2){
    exit(EXIT_FAILURE);
  }
  /*
  ** reading 1 and printing basportnr and 2 arugment which is the id of node
  */
  baseport = atoi(argv[1]);
  printf("Port: %ld\n", baseport);
  id = atoi(argv[2]);

  /*
  ** mallocing place for neighbour struct that contains nunmber of nodes
  */
  if(argc >= 3){
    nodene = malloc(sizeof(struct neighbour*)*number_of_nodes);
    for(j = 0; j < number_of_nodes; j++){
      div = argv[j+3];
      nodene[j] = add_neighbour(div);
    }
  }

  //Setting up socket connection
  printf("Setting up connection socket\n");

  tcp_socket = tcp_socket_client(baseport);
  edge_info(id, j, nodene, tcp_socket);

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
struct neighbour* add_neighbour(char* c){
  struct neighbour* pointer;

  pointer = malloc(sizeof(struct neighbour));
  pointer->id = (int)atoi(strtok(c, ":"));
  pointer->weight = (int)atoi(strtok(NULL,""));
  return pointer;
}
/*
**sends edge information to routing_server
*/
void edge_info(int adress,int num,struct neighbour** neighbour, int socket){
  int i;
  unsigned long pass;
  char message[MAXDATASIZE];

  sprintf(message, "Node id: %d\n", adress);
  sprintf(message, "Number of neighbours: %d\n", num);
  //printf("Number of neighbours: %s\n", msg);
  //printf("%s\n", msg);
  for(i = 0; i < num; i++){
    sprintf(message, "%s %d : %d\n", message, neighbour[i]->id, neighbour[i]->weight);
  }
  printf("%s\n", message);

  /*
  ** sending data on socket
  */
  pass = send(socket,message, sizeof(message), 0);

  /*
  ** checking if right number of messages are sent
  */
  if(pass < sizeof(message)){
    perror("send() error");
    exit(1);
  }


}
