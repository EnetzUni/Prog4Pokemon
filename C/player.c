#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "sqlite3.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"
#include "db.h"

Player* createPlayer(char nickname[], char password[], bool gender, PokemonPlayer** listPokemon, int listPokemonSize, int maxLvL, int story) {
    Player* player = malloc(sizeof(Player));
    if (!player) return NULL;

    // Copy strings
    strncpy(player->nickname, nickname, sizeof(player->nickname) - 1);
    player->nickname[sizeof(player->nickname) - 1] = '\0';

    strncpy(player->password, password, sizeof(player->password) - 1);
    player->password[sizeof(player->password) - 1] = '\0';

    // Set basic values
    player->gender = gender;
    player->listPokemonSize = listPokemonSize;
    player->maxLvL = maxLvL;
    player->story = story;

    // Always allocate memory for the list (e.g., up to 6)
    player->listPokemon = malloc(sizeof(PokemonPlayer*) * 6);
    if (!player->listPokemon) {
        // Return partially constructed object if needed, or handle gracefully
        return player;
    }

    // If listPokemon is provided, copy pointers
    if (listPokemon) {
        for (int i = 0; i < listPokemonSize && i < 6; ++i) {
            player->listPokemon[i] = listPokemon[i];
        }
        for (int i = listPokemonSize; i < 6; ++i) {
            player->listPokemon[i] = NULL;
        }
    } else {
        // Otherwise, initialize all to NULL
        for (int i = 0; i < 6; ++i) {
            player->listPokemon[i] = NULL;
        }
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

    if (player->listPokemon == NULL || player->listPokemonSize <= 0) {
        printf("No PokEmon available.\n");
        printf("========================\n");
        return;
    }

    // Print pointers debug info:
    printf("Pokemon list pointer: %p\n", (void*)player->listPokemon);
    printf("Pokemon list size: %d\n", player->listPokemonSize);
    for (int i = 0; i < player->listPokemonSize; ++i) {
        printf("Slot %d pointer: %p\n", i, (void*)player->listPokemon[i]);
    }

    for (int i = 0; i < player->listPokemonSize; ++i) {
        PokemonPlayer* poke = player->listPokemon[i];

        if (poke == NULL) {
            printf("\n--- Pokemon Slot %d is empty ---\n", i + 1);
            continue;
        }

        if ((uintptr_t)poke < 0x1000) {
            printf("\n--- Pokemon Slot %d has invalid pointer: %p ---\n", i + 1, (void*)poke);
            continue;
        }

        printf("\n--- Pokemon Slot %d ---\n", i + 1);
        printPokemonPlayer(poke);
    }

    printf("========================\n");
}

void printTeam(Player* player) {
    if (!player) {
        printf("No Player to get Team.\n");
        return;
    } else if (player->listPokemonSize == 0)
    {
        printf("There are no Pokemon in your team.\n");
    }
    
    if (player->listPokemon != NULL)
    {
        for (int i = 0; i < player->listPokemonSize; i++)
        {
            printPokemonPlayer(player->listPokemon[i]);
        }
    }
}

void removePlayerPokemonPlayer(sqlite3* db, Player* player, int playerIndex) {
    player->listPokemon[playerIndex] = NULL;

    for (int i = playerIndex; i < player->listPokemonSize - 1; ++i) {
        player->listPokemon[i] = player->listPokemon[i + 1];
    }

    player->listPokemon[player->listPokemonSize - 1] = NULL;
    player->listPokemonSize--;

    insertPlayerTeam(db, player);
}

int addPlayerPokemonPlayer(sqlite3* db, Player* player, PokemonPlayer* pokemon) {
    if (player->listPokemon == NULL) {
        // Allocate array for up to 6 PokemonPlayer pointers
        player->listPokemon = (PokemonPlayer**) malloc(sizeof(PokemonPlayer*) * 6);
        if (player->listPokemon == NULL) {
            printf("Error allocating memory for player's Pokemon list.\n");
            return 0; // failure
        }
        player->listPokemonSize = 0; // initialize size since we just allocated
    }

    if (player->listPokemonSize >= 6) {
        printf("Cannot add more Pokemon: team is full.\n");
        return 0; // failure: no room
    }

    // Add the new Pokemon pointer and increment size
    player->listPokemon[player->listPokemonSize] = pokemon;
    player->listPokemonSize++;

    printPokemonPlayer(pokemon);

    // Update the DB
    if (!insertPlayerTeam(db, player)) {
        printf("Failed to update player team in DB.\n");
        return 0; // failure
    }

    return 1; // success
}