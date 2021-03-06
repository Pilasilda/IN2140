#include "header.h"

int main(int argc, char* argv[]){
  struct neighbour** nodene = {0};
  int id,tcp_socket,port;
  int i;

  number_of_nodes = argc-3;
  int baseport;
  int j=0;
  char *div;

  if(argc < 2){
    exit(EXIT_FAILURE);
  }

  baseport = atoi(argv[1]);
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
  /*Setting up socket connection*/
  tcp_socket = tcp_socket_client(baseport);
  if(tcp_socket == 0){
    exit(EXIT_FAILURE);
  }
  /*
  ** reading 1 and printing basportnr and 2 arugment which is the id of node
  */
  printf("Port: %d", baseport);
  printf("\nNode id: %d", id);
  edge_info(id, j, nodene, tcp_socket);

  /*freeing allocated memory*/
  for(i = 0; i<number_of_nodes; ++i){
    free(nodene[i]);
  }
  free(nodene);

  /*
  1. Vente på tilkoblinger fra noder
  2. Motta adresse og kant-info
  3. Kaller metode som tester at hver kant er rapportert to ganger
  4. Kaller dijsktra for å beregne korteste vei fra 1 til alle noder
  5. sender/kaller på metode som sender ruting-tabeller
  */


}

/*
** method that creates tcp socket for node
*/
int tcp_socket_client(int ports){
  int counter,tcp_socket_client = 1;
  struct sockaddr_in socket_address;
  struct sockaddr_in serv_addr;


  if((tcp_socket_client = socket(AF_INET, SOCK_STREAM,0)) == -1){
    printf("Failed creating socket()\n");
    perror("socket");
    exit(EXIT_FAILURE);
  }

  //printf("TCP socket for client created \n");
  /*Specifying connection and port, assign ip and port*/
  setsockopt(tcp_socket_client, SOL_SOCKET, SO_REUSEADDR,&counter, sizeof(int));
  socket_address.sin_family = AF_INET;
  socket_address.sin_port = htons(SERVER_PORT);
  socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");

  printf("Connection to server %d, port %d\n", ports, SERVER_PORT);
  if(connect(tcp_socket_client, (struct sockaddr*)&socket_address, sizeof(serv_addr)) < 0){
    printf("Failed connect()\n");
    perror("connect");
    return 1;
  }
  return tcp_socket_client;
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
  /*char buffer to store message*/
  char message[MAXDATASIZE];

  /*Using sprintf function, because instead of printing this information to console/terminal it will store it on a char buffer in my case message defined over*/
  sprintf(message, "Node id: %d\n", adress);
  sprintf(message, "\nNumber of neighbours: %d\nNeighbours&weight:\n", num);

  /*Looping through all the possible neighbours passed as arguments*/
  for(i = 0; i < num; i++){
    sprintf(message, "%s %d : %d\n", message, neighbour[i]->id, neighbour[i]->weight);
  }

  /*Printing all information that is stored in charbuffer message, also the previous messages that is stored, like id of node and number of arguments*/
  printf("%s\n", message);

  /*sending data to socket*/
  pass = send(socket,message, sizeof(message), 0);

  /*checking if right number of messages are sent*/
  if(pass < sizeof(message)){
    perror("send() error");
    exit(1);
  }
  //printf("Sending %lu bytes. \n", pass);
}
