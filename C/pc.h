#ifndef PC_H
#define PC_H

#include "pokemon.h"

typedef struct {
    PokemonPlayer** pcList; // Dynamic array to store PokemonPlayer
    int pcListSize;              // Current size of the PC list
} PC;

PC* createPC();
void showPC(PC* pc);
void addPokemonToPC(PC* pc, PokemonPlayer* pokemonPlayer);
void removePokemonFromTeam(PokemonPlayer listPokemon[6], PC* pc);
void addPokemonToTeam(PokemonPlayer listPokemon[6], PC* pc);

#endif
