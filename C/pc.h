#ifndef PC_H
#define PC_H

#include "pokemon.h"

typedef struct {
    PokemonPlayer** pcList;
    int pcListSize;
} PC;

PC* createPc(PokemonPlayer**, int);
void printPc(PC* pc);

#endif
