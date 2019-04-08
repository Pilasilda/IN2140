#include "drift.h"

struct ruter **rutere;
struct ruter *r;

/*
* reads inputfile and create datastructure
*/
void read_file (char *filename){
    FILE *file = fopen(filename,"r");
    int i;

    if(file == NULL){
      printf("Error! COULDNT open file %s\n", filename);
      exit(1);
   }

    fread(&N,sizeof(int), 1, file);
    //allocating memory for dobbelpointer, array of structs
    rutere = malloc(sizeof(struct ruter*) *N);

    for(i=0; i < N; i++){
        fseek(file, 1, SEEK_CUR); // skips line
        r = malloc(sizeof(struct ruter));
        rutere[i] = r;

        //routerid
        fread(&r->ruterid, sizeof(unsigned char), 1, file);
        //printf("Ruter-id:%d\n", (unsigned char) r->ruterid);

        //flagg
        fread(&r->flagg, sizeof(unsigned char), 1, file);
        //printf("Ruter-flagg:%d\n", (unsigned char) r->flagg);

        //length
        fread(&r->lengde, sizeof(unsigned char), 1, file);
        //printf("Ruter-lengde:%u\n", (unsigned char) r->lengde);

        //Routername
        fread(&r->produsent_lengde,r->lengde-1,1, file);
        //printf("Produsent:%s\n",r->produsent_lengde);
        //printf("*\n");
    }
    unsigned char line;
    int t;
    while((t = fread(&line,sizeof(unsigned char),1,file))!= 0){
        unsigned char k1;
        unsigned char k2;
        int x,y,z;

        fread(&k1, sizeof(unsigned char), 1, file);
        fread(&k2, sizeof(unsigned char), 1, file);

        for(x = 0; x < N; x++){
            if(rutere[x]->ruterid == k1){
              break;
            }
        }

        for(y=0; y< N; y++){
            if(rutere[y]->ruterid == k2){
                break;
            }
        }

        for(z=0; z < 10; z++){
            if(rutere[x]->koblinger[z] == NULL){
                rutere[x]->koblinger[z] = rutere[y];
                //printf("%d->%d\n",rutere[x]->ruterid, rutere[x]->koblinger[z]->ruterid);
                goto her;
            }

        if(EOF){
          break;
        }
      }
      her:
      printf("");
    }
    fclose(file);
}

/*
* write to file
*/
void skrive_til_fil(char* filename){
    printf("\n*****************\n");
    printf("Lagrer i fil: %s\n",filename);

    int teller=0;
    char nylinje[1]={'\n'};
    int i, j;

    //open file for writing in binarymode
    FILE *file = fopen(filename, "w+");

    if(file == NULL){
      perror("Errror!");
    }

    if(file){
      fwrite(&N, sizeof(int), 1, file);
      fwrite(nylinje, sizeof(char), 1, file);

    struct ruter *r;

    while(teller < N){
      r = rutere[teller];

      if(r){
        unsigned char id = r->ruterid;
        unsigned char flagg = r->flagg;
        unsigned char lengde = r->lengde;
        char* modell = r->produsent_lengde;


        fwrite(&id, sizeof(unsigned char), 1, file);
        fwrite(&flagg, sizeof(unsigned char), 1, file);
        fwrite(&lengde, sizeof(unsigned char), 1, file);
        fwrite(modell,sizeof(char), (lengde-1), file);
        fwrite(nylinje, sizeof(char), 1, file);
      }
      teller++;
    }
  }

    //connections
    for(i=0; i < N; i++){
      for(j=0; j < 10;j++){
        if(rutere[i] != NULL){
          if(rutere[i]->koblinger[j] != NULL){
            fwrite(&rutere[i]->ruterid, sizeof(unsigned char), 1, file);
            fwrite(&rutere[i]->koblinger[j]->ruterid, sizeof(unsigned char), 1, file);
            fwrite(&teller, sizeof(char), 1, file);
          }
        }
      }
    }
    fclose(file);
}

/*
* prints information about router and neighbours of router
*/
void print(int id){
  int i;
  printf("***RUTER-INFO***\n");
  printf("Ruterid: %d\n", (unsigned char) rutere[id]->ruterid);
  printf("Flagg: %d\n", (unsigned char) rutere[id]->flagg);
  printf("Produsent: %s\n", rutere[id]->produsent_lengde);
  printf("\n");
  printf("*******\n");

  for(i = 0; i < 10; i++) {
    if(rutere[id]->koblinger[i] != NULL) {
      printf("Nabo: %d\n",(unsigned char)rutere[id]->koblinger[i]->ruterid);
      printf("*********");
    }
  }
}

/*
* method used to check if sett_flag prints correctly
*/
void printBin(char c){
  int i = 7;

  for(i = 7; i >= 0; --i){
    putchar((c & (1 << i)) ? '1' : '0');
  }
  putchar('\n');
}

/*
* sett_flag, flaggbit 0,1,2 can only be 0 or 1, either on or off.
*/
void sett_flag(unsigned char id, unsigned char flaggverdi, unsigned char value){
    if(flaggverdi == 0){
      rutere[id]->flagg ^= 1;
      //printBin(rutere[id]->flagg);
    }else if(flaggverdi == 1){
      rutere[id]->flagg ^= 2;
    }else if(flaggverdi == 2){
      rutere[id]->flagg ^= 4;
      //printf("5GHz, satt til %d ", rutere[id]->flagg);
    }else if(flaggverdi == 3){
      printf("Errorrrr!! Unused flaggbit!!\n");
    }else if(flaggverdi == 4){
      if(value >= 0 && value <= 15){
        rutere[id]->flagg <<4;
        rutere[id]->flagg >>4;
        value = value <<4;
        rutere[id]->flagg = rutere[id]->flagg|value;
        printBin(rutere[id]->flagg);
        printf("Endringsnummer:%d",rutere[id]->flagg);
      }
    }else{
      printf("ERROR!!");
    }
}


/*
* Modify modelname
*/
void sett_modell(unsigned char id){
    int i;
    char* produsent = strtok(NULL, "");
    for(i = 0; i < N; i++){
        if(rutere[i] != NULL){
            if(rutere[i]->ruterid == id){
                rutere[i]->lengde= strlen(produsent)-1;
                printf("\nGammelt modellnavn: %s\n", rutere[i]->produsent_lengde);
                strcpy(rutere[i]->produsent_lengde,produsent);
                printf("Nyttmodellnavn: %s\n",rutere[i]->produsent_lengde);
            }
        }
    }
}

/*
* adding connection between routers
*/
void legg_til_kobling(int id1, int id2){
  int a, b;
  for(a = 0; a<10; a++){
    if(rutere[id1]->koblinger[a] == NULL){
      rutere[id1]->koblinger[a] = rutere[id2];
      printf("\n");
      printf("\nKobling lagt til mellom ruter %d og", rutere[id2]->ruterid);
      break;
    }
  }

  for(b = 0; b<10; b++){
    if(rutere[id2]->koblinger[b] == NULL){
      rutere[id2]->koblinger[b] = rutere[id1];
      printf(" %d. \n", rutere[id1]->ruterid);
      break;
    }
  }
}


/*
* delete connection between routers
*/
void kobling(unsigned char r){
  int x,y;
  for(x=0; x < N; x++){
    for(y=0; y < 10; y++){
      if(rutere[x]->koblinger[y] != NULL){
        if(rutere[x]->koblinger[y]->ruterid == r){
          printf("\n");
          printf("Kobling slettet mellom: %d %d\n", rutere[x]->ruterid,rutere[x]->koblinger[y]->ruterid);
        }
      }
    }
  }
}


/*
* delete router
*/
void slett_router(unsigned char ruter){
  int i = 0;
  printf("\n");
  printf("***SLETT-KOBLING***");
  kobling(ruter);
  printf("\n***SLETT RUTER***\n");
  free(rutere[ruter]);
  rutere[ruter] = NULL;
  i = i-1;
  printf("Ruterid: %d slettet",ruter);
  printf("\n");
}

/*
* Find route between routers
*/
/*
int finnes_rute(int ruterEn, int ruterTo){
  int i = 0;

  struct ruter* tmp = rutere[ruterEn];
  tmp->visited = 1;

  if(ruterEn == ruterTo){
    printf("Rute finnes\n");
    return 1;
  }else{
    for(i=0; i < 10; i++){
      if(rutere[ruterEn]->koblinger[i] == NULL){
        printf("Tom plass\n");
      }else if(rutere[ruterEn]->koblinger[i]->visited == 1){
        printf("Rute er besøkt allerede, går videre\n");
      }else if(rutere[ruterEn]->koblinger[i]->ruterid == ruterTo){
        printf("Ruten finnes\n");
        return 1;
      }else{
        int j = finnes_rute(rutere[ruterEn]->koblinger[i]->ruterid, ruterTo);
        if(j == 1){
          printf("Rute finnes");
          return 1;
        }else{
          return 0;
        }
      }
    }
    return 0;
  }
}
*/

/*
* counts line of file
*/
int linjer(FILE* file){
  unsigned long teller = ftell(file);
  int t = 0;
  char c;

  for(c = getc(file); c !=EOF; c=getc(file)){
    if(c == '\n'){
      t++;
    }
  }
  fseek(file,teller, SEEK_SET);
  return t;
}


/*
* reading commandfile
*/
void read_command(char* file){
    FILE* command_file = fopen(file,"r");
    //command_file = fopen(file,"r");
    int i;
    char max[ANTALL_LINJER];
    int count = linjer(command_file);

    if(command_file == NULL){
      perror("COULDNT OPEN FILE.");
      exit(1);
    }

    for(i =0; i< count; i++){
      fgets(max, sizeof(max),command_file);
      char *commandLine = strtok(max, " ");
      int ruter = atoi(strtok(NULL, " "));

      if(strcmp(commandLine, "print") == 0){
        print(ruter);
      }else if(strcmp(commandLine, "sett_modell") == 0){
        sett_modell(ruter);
      }else if(strcmp(commandLine, "legg_til_kobling") == 0){
        //ruter-for ruter forste ruter, ruter2 for noden den skal legges kobling til
        int ruterTo = atoi(strtok(NULL, " "));
        legg_til_kobling(ruter, ruterTo);
      }else if(strcmp(commandLine, "slett_router") == 0){
        slett_router(ruter);
      }else if(strcmp(commandLine, "sett_flag") == 0){
        unsigned char falagg = atoi(strtok(NULL, " "));
        unsigned char value = atoi(strtok(NULL, " "));
        sett_flag(ruter, falagg, value);
      }/*else if(strcmp(commandLine, "finnes_rute") == 0){
        int ruterTo = atoi(strtok(NULL, " "));
        printf("%d->%d", ruter, ruterTo);
        finnes_rute(ruter, ruterTo);
    }*/
  }
  fclose(command_file);
}

/*
* mainmethod
*/
int main(int argc, char* argv[]){
    int i;
    if(argc < 1){
      printf("**********\n");
      return 0;
    }

    read_file(argv[1]);
    read_command(argv[2]);
    skrive_til_fil(argv[1]);
    //read_file("test");

    for(i= 0; i < N; i++){
      free(rutere[i]);
    }
    free(rutere);
}

//I 10 ruterfilen blir det gjort 14 allokeringer, og det ble freet 14. 5224 bytes allokert.
//I 50 ruterfilen blir det gjort 54 allokeringer, og det ble freet 54. 19304 bytes allokert.
