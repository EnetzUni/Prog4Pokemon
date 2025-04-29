#ifndef PC_H
#define PC_H

#include "pokemon.h"

typedef struct {
        /// List of the Pokemon stored in the Pc.
        PokemonPlayer** listPokemon;
} Pc;

#endif