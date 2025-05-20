#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pokemon.h"
#include "movement.h"
#include "player.h"

Player* createPlayer(char nickname[], char password[], bool gender, PokemonPlayer* listPokemon[6], int listPokemonSize, int maxLvL, int story) {
    Player* player = malloc(sizeof *player);
    if (!player) {
        return NULL;
    }

    strncpy(player->nickname, nickname, sizeof player->nickname - 1);
    player->nickname[sizeof player->nickname - 1] = '\0';

    strncpy(player->password, password, sizeof player->password - 1);
    player->password[sizeof player->password - 1] = '\0';

    player->gender = gender;
    player->listPokemonSize = listPokemonSize;
    player->maxLvL = maxLvL;
    player->story = story;

    for (int i = 0; i < player->listPokemonSize; ++i) {
        player->listPokemon[i] = listPokemon[i];
    }

    return player;
}

void printPlayer(Player* player) {
    if (!player) {
        printf("No Player to print.\n");
        return;
    }

    printf("===== Player Info =====\n");
    printf("Nickname  : %s\n", player->nickname);
    printf("Password  : %s\n", player->password);
    printf("Gender    : %s\n", player->gender ? "Male" : "Female");
    printf("Max LvL   : %d\n", player->maxLvL);
    printf("Story Part: %d\n", player->story);

    for (int i = 0; i < player->listPokemonSize; ++i) {
        printf("\n--- Pokemon Slot %d ---\n", i + 1);
        printPokemonPlayer(player->listPokemon[i]);
    }
    printf("========================\n");
}