#include <stdio.h>
#include <stdlib.h>
#include "pc.h"
PC* createPC() {
    PC* pc = malloc(sizeof(PC));
    pc->pcList = NULL;
    pc->pcCount = 0;
    return pc;
}
void showPC(PC* pc) {
    if (pc->pcCount == 0) {
        printf("PC is empty.\n");
        return;
    }
    printf("----- PC List -----\n");
    for (int i = 0; i < pc->pcCount; i++) {
        printPokemonPlayer(&pc->pcList[i]);
    }
    printf("--------------------\n");
}

void addPokemonToPC(PC* pc, PokemonPlayer* pokemonPlayer) {
    pc->pcList = realloc(pc->pcList, (pc->pcCount + 1) * sizeof(PokemonPlayer));
    pc->pcList[pc->pcCount] = *pokemonPlayer; // Add the PokemonPlayer to PC
    pc->pcCount++;
}

void removePokemonFromTeam(Player* player, PC* pc) {
    printf("Do you want to remove a Pokemon from your team? (1: Yes, 0: No): ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Select a Pokemon to remove from your team:\n");
        for (int i = 0; i < 6; i++) {
            if (player->listPokemon[i] != NULL) {
                printf("%d: ", i + 1);
                printPokemonPlayer(&player->listPokemon[i]);
            }
        }
        int index;
        printf("Enter the number of the Pokemon to remove: ");
        scanf("%d", &index);
        index--; // Adjust for 0-based index
        if (index >= 0 && index < 6 && player->listPokemon[index] != NULL) {
            addPokemonToPC(pc, &player->listPokemon[index]);
            player->listPokemon[index] = NULL; // Remove from team
            printf("Pokemon removed from team and added to PC.\n");
        } else {
            printf("Invalid selection.\n");
        }
    }
}
void addPokemonToTeam(Player* player, PC* pc) {
    printf("Do you want to add a Pokemon from PC to your team? (1: Yes, 0: No): ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Select a Pokemon from PC:\n");
        showPC(pc);
        int index;
        printf("Enter the number of the Pokemon to add: ");
        scanf("%d", &index);
        index--; // Adjust for 0-based index
        if (index >= 0 && index < pc->pcCount) {
            for (int i = 0; i < 6; i++) {
                if (player->listPokemon[i] == NULL) {
                    player->listPokemon[i] = pc->pcList[index]; // Add to team
                    // Shift remaining Pokemon in PC
                    for (int j = index; j < pc->pcCount - 1; j++) {
                        pc->pcList[j] = pc->pcList[j + 1];
                    }
                    pc->pcCount--;
                    pc->pcList = realloc(pc->pcList, pc->pcCount * sizeof(PokemonPlayer));
                    printf("Pokemon added to team.\n");
                    return;
                }
            }
            printf("Your team is full.\n");
        } else {
            printf("Invalid selection.\n");
        }
    }
}