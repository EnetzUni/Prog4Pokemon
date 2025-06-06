#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Movement.h"
#include "type.h"
#include "category.h"
#include "status.h"
#include "sqlite3.h"
#include "db.h"

Movement* createMovement(int id, char name[], Type type, Category category, Status status, int statusaccuracy, int power, int accuracy) {
    Movement* movement = malloc(sizeof* movement);
    if (movement == NULL) {
    return NULL;
    }

    movement->id             = id;
    movement->type           = (Type) type;
    movement->category       = (Category) category;
    movement->status         = (Status) status;
    movement->statusaccuracy = statusaccuracy;
    movement->power          = power;
    movement->accuracy       = accuracy;

    // Safely copy name into fixed‐size buffer, then null‑terminate
    strncpy(movement->name, name, sizeof movement->name - 1);
    movement->name[sizeof movement->name - 1] = '\0';  // ensure termination :contentReference[oaicite:2]{index=2}

    return movement;
}

void printMovement(Movement* movement) {
    if (movement == NULL) {
    printf("No Movement to print.\n");
    return;
    }

    printf("----- Movement #%d -----\n", movement->id);
    printf("Name            : %s\n", movement->name);
    printf("Type            : %s\n", getTypeName((Type) movement->type));
    printf("Category        : %s\n", getCategoryName((Category) movement->category));
    printf("Status          : %s\n", getStatusName((Status) movement->status));
    printf("Status Chance   : %d%%\n", movement->statusaccuracy);
    printf("Power           : %d\n", movement->power);
    printf("Accuracy        : %d%%\n", movement->accuracy);
    printf("-------------------------\n");
}

void printMovementSmall(Movement* movement) {
    if (movement == NULL) {
    printf("No Movement to print.\n");
    return;
    }

    printf("----- Movement #%d -----\n", movement->id);
    printf("Name            : %s\n", movement->name);
}

Movement** createRandomMovementList(sqlite3* db)
{
    Movement** randomMovemets = malloc(sizeof(Movement*) * 4);
    int usedIds[4];
    int count = 0;

    while (count < 4) {
        int id = (rand() % 934) + 1;

        // Verificar si el ID ya fue usado
        int duplicate = 0;
        for (int j = 0; j < count; j++) {
            if (usedIds[j] == id) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            Movement* movement = loadMovement(db, id);
            if (movement->power != 0)
            {
                randomMovemets[count] = movement;
                usedIds[count] = id;
                count++;
            }
        }
    }
    return randomMovemets;
}