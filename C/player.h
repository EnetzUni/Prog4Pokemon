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
    PokemonPlayer** listPokemon;

    /// List of the size of Pokemon in the player's team.
    int listPokemonSize;

    /// Maximum level of Pokemon that the player can encounter.
    int maxLvL;

    /// Current part of the story where the player is.
    int story;
} Player;

#ifdef __cplusplus
extern "C" {
#endif

Player* createPlayer(char[], char[], bool, PokemonPlayer**, int, int, int);
void printPlayer(Player*);
void printPlayerSmall(Player*);
void printTeam(Player*);
void removePlayerPokemonPlayer(sqlite3*, Player*, int);
int addPlayerPokemonPlayer(sqlite3*, Player*, PokemonPlayer*);

#ifdef __cplusplus
}
#endif

#endif
