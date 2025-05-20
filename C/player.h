#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "pokemon.h"

typedef struct {
        /// The player's nickname.
        char nickname[255];
    
        /// The player's password.
        char password[255];
    
        /// The player's gender.
        bool gender;
    
        /// List of the Pokemon in the player's team.
        PokemonPlayer* listPokemon[6];

        /// List of the size of Pokemon in the player's team.
        int listPokemonSize;

        /// Maximum level of Pokemon that the player can encounter.
        int maxLvL;

        /// Current part of the story where the player is.
        int story;
} Player;

createPlayer(char[], char[], bool, PokemonPlayer*[6], int, int, int);
printPlayer(Player*);

#endif