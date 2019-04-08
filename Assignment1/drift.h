#ifndef DRIFT_H_
#define DRIFT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANTALL_LINJER 256
#define MAXANTALLRUTERE 10
#define BUFFER 253

//Global variable for aa holde paa antall rutere i filen
int N =0;

struct ruter{
    unsigned char ruterid;
    unsigned char flagg;
    unsigned char lengde;
    char produsent_lengde[BUFFER];
    struct ruter *koblinger[10];
    int visited; //1 hvis true, 0 hvis false
};

void read_file(char*);
void print(int);
void printBin(char);
void sett_modell(unsigned char);
void sett_flag(unsigned char, unsigned char, unsigned char);
void skrive_til_fil(char*);
void legg_til_kobling(int, int);
void kobling(unsigned char);
void slett_router(unsigned char);
int linjer(FILE*);
void read_command(char*);
int finnes_ruter(int ruterEn, int ruterTo);

#endif
