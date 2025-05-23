#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pc.h"

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

/*addPcPokemonPlayer(PC* pc, PokemonPlayer pokemon) {

}*/