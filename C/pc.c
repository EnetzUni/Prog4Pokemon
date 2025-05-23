#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "pc.h"
#include "player.h"
#include "db.h"

PC* createPc(char nickname[], PokemonPlayer** pcList, int pcListSize) {
    PC* pc = malloc(sizeof* pc);
    if (pc == NULL) {
        return NULL;
    }

    strncpy(pc->nickname, nickname, sizeof pc->nickname - 1);
    pc->nickname[sizeof pc->nickname - 1] = '\0';
    pc->pcList     = pcList;
    pc->pcListSize = pcListSize;

    return pc;
}

void printPc(PC* pc) {
    if (!pc) {
        printf("No PC to print.\n");
        return;
    }

    printf("===== PC =====\n");
    printf("Nickname  : %s\n", pc->nickname);
    for (int i = 0; i < pc->pcListSize; ++i) {
    printf("--- PokemonPlayer slot %d ---\n", i + 1);
    printPokemonPlayer(pc->pcList[i]);
    }
    printf("============================\n");
}

void addPcPokemonPlayer(sqlite3* db, PC* pc, PokemonPlayer* pokemon) {
    PokemonPlayer** updatedPcList = realloc(pc->pcList, (pc->pcListSize + 1) * sizeof(PokemonPlayer*));
    pc->pcList = updatedPcList;
    pc->pcList[pc->pcListSize] = pokemon;
    pc->pcListSize++;

    insertPc(db, pc);
}

void removePcPokemonPlayer(sqlite3* db, PC* pc, int pcIndex) {
    pc->pcList[pcIndex] = NULL;

    for (int i = pcIndex; i < pc->pcListSize - 1; ++i) {
        pc->pcList[i] = pc->pcList[i + 1];
    }

    pc->pcList[pc->pcListSize - 1] = NULL;
    pc->pcListSize--;

    insertPc(db, pc);
}

void switchPcTeamPokemonPlayer(sqlite3* db, PC* pc, int pcIndex, Player* player, int playerIndex) {
    PokemonPlayer* pokemonplayerpc = pc->pcList[pcIndex];
    PokemonPlayer* pokemonplayerteam = player->listPokemon[playerIndex];

    removePcPokemonPlayer(db, pc, pcIndex);
    addPcPokemonPlayer(db, pc, pokemonplayerteam);

    removePlayerPokemonPlayer(db, player, playerIndex);
    addPlayerPokemonPlayer(db, player, pokemonplayerpc);
}