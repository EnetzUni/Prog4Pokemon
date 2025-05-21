#include <stdio.h>
#include <stdlib.h>
#include "pc.h"

PC* createPC() {
    malloc()
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

// Function to manage the PC menu interactively
void managePC(PokemonPlayer listPokemon[6], PC* pc) {
    int choice;
    do {
        printf("=== Welcome to the Pokemon Management ===\n");
        printf("1. View team Pokemon list\n");
        printf("2. View PC Pokemon list\n");
        printf("3. Remove a Pokemon from the team\n");
        printf("4. Add a Pokemon to the team\n");
        printf("5. Exit PC management\n");
        printf("Please select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("=== Team Pokemon ===\n");
                for (int i = 0; i < 6; i++) {
                    if (listPokemon[i].pokeid != 0) {
                        printf("%d: %s\n", i + 1, listPokemon[i].nickname);
                    }
                }
                printf("Select a Pokemon to see details (0 to return): ");
                int indexTeam;
                scanf("%d", &indexTeam);
                if (indexTeam > 0 && indexTeam <= 6 && listPokemon[indexTeam - 1].pokeid != 0) {
                    printPokemonPlayer(&listPokemon[indexTeam - 1]);
                }
                break;

            case 2:
                showPC(pc);
                printf("Select a Pokemon to see details (0 to return): ");
                int indexPC;
                scanf("%d", &indexPC);
                if (indexPC > 0 && indexPC <= pc->size) {
                    printPokemonPlayer(&pc->pcList[indexPC - 1]);
                }
                break;

            case 3:
                removePokemonFromTeam(listPokemon, pc);
                break;

            case 4:
                addPokemonToTeam(listPokemon, pc);
                break;

            case 5:
                printf("Exiting PC management...\n");
                break;

            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
        printf("\n");
    } while (choice != 5);
}

