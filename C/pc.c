#include <stdio.h>
#include <stdlib.h>
#include "pc.h"

PC* createPc(PokemonPlayer** pcList, int pcListSize) {
    PC* pc = malloc(sizeof* pc);
    if (pc == NULL) {
        return NULL;
    }

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
    for (int i = 0; i < pc->pcListSize; ++i) {
    printf("--- PokemonPlayer slot %d ---\n", i + 1);
    printPokemonPlayer(&pc->pcList[i]);
    }
    printf("============================\n");
}

addPcPokemonPlayer(PC* pc, PokemonPlayer pokemon) {

}