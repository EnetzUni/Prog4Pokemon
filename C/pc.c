#include <stdio.h>
#include <stdlib.h>
#include "pc.h"

PC* createPC() {
    PC* pc = malloc(sizeof(PC));
    pc->pcList = NULL;
    pc->size = 0;
    return pc;
}

void showPC(PC* pc) {
    if (pc->size == 0) {
        printf("PC is empty.\n");
        return;
    }
    printf("----- PC List -----\n");
    for (int i = 0; i < pc->size; i++) {
        printf("%d: %s\n", i + 1, pc->pcList[i].nickname);
    }
    printf("--------------------\n");
}

void addPokemonToPC(PC* pc, PokemonPlayer* pokemonPlayer) {
    pc->pcList = realloc(pc->pcList, (pc->size + 1) * sizeof(PokemonPlayer));
    pc->pcList[pc->size] = *pokemonPlayer; // Add the PokemonPlayer to the PC
    pc->size++;
}

void removePokemonFromTeam(PokemonPlayer listPokemon[6], PC* pc) {
    printf("Do you want to remove a Pokemon from your team? (1 for Yes, 0 for No): ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Select a Pokemon to remove from your team:\n");
        for (int i = 0; i < 6; i++) {
            if (listPokemon[i].pokeid != 0) { // Assuming pokeid 0 means empty slot
                printf("%d: %s\n", i + 1, listPokemon[i].nickname);
            }
        }
        int index;
        printf("Enter the number of the Pokemon to remove: ");
        scanf("%d", &index);
        if (index > 0 && index <= 6 && listPokemon[index - 1].pokeid != 0) {
            addPokemonToPC(pc, &listPokemon[index - 1]);
            listPokemon[index - 1].pokeid = 0; // Remove from team
            printf("Pokemon removed from team and added to PC.\n");
        } else {
            printf("Invalid selection.\n");
        }
    }
}

void addPokemonToTeam(PokemonPlayer listPokemon[6], PC* pc) {
    printf("Do you want to add a Pokemon from PC to your team? (1 for Yes, 0 for No): ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Select a Pokemon from PC to add to your team:\n");
        showPC(pc);
        int index;
        printf("Enter the number of the Pokemon to add: ");
        scanf("%d", &index);
        if (index > 0 && index <= pc->size) {
            for (int i = 0; i < 6; i++) {
                if (listPokemon[i].pokeid == 0) { // Find an empty slot
                    listPokemon[i] = pc->pcList[index - 1]; // Add to team
                    pc->pcList[index - 1].pokeid = 0; // Remove from PC
                    printf("Pokemon added to team.\n");
                    return;
                }
            }
            printf("No space available in team.\n");
        } else {
            printf("Invalid selection.\n");
        }
    }
}
