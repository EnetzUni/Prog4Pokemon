#ifndef PC_H
#define PC_H

#include "pokemon.h"

typedef struct {
    /// The player's nickname.
    char nickname[255];

    /// List of PokemonPlayer inside the PC.
    PokemonPlayer** pcList;

    /// Size of PokemonPlayer list inside the PC.
    int pcListSize;
} PC;

PC* createPc(char[], PokemonPlayer**, int);
void printPc(PC* pc);
int addPcPokemonPlayer(sqlite3*, PC*, PokemonPlayer*);
void removePcPokemonPlayer(sqlite3*, PC*, int);

#endif
