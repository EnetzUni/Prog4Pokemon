#ifndef PC_H
#define PC_H

#include "pokemon.h"

typedef struct {
        /// List of the Pokemon stored in the Pc.
        PokemonPlayer* pcList;
        int count; 
} Pc;

PC* createPC();
void showPC(PC* pc);
void addPokemonToPC(PC* pc, PokemonPlayer* pokemonPlayer);
void removePokemonFromTeam(Player* player, PC* pc);
void addPokemonToTeam(Player* player, PC* pc);

#endif
