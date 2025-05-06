#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Movement.h"
#include "type.h"
#include "category.h"
#include "status.h"

Movement* createMovement(int id, char name[], Type type, Category category, Status status, int statusaccuracy, int power, int accuracy) {
    Movement* movement = malloc(sizeof* movement);
    if (movement == NULL) {
    return NULL;
    }

    movement->id             = id;
    movement->type           = type;
    movement->category       = category;
    movement->status         = status;
    movement->statusaccuracy = statusaccuracy;
    movement->power          = power;
    movement->accuracy       = accuracy;

    // Safely copy name into fixed‐size buffer, then null‑terminate
    strncpy(movement->name, name, sizeof movement->name - 1);
    movement->name[sizeof movement->name - 1] = '\0';  // ensure termination :contentReference[oaicite:2]{index=2}

    return movement;
}

void printMovement(const Movement* movement) {
    if (movement == NULL) {
    printf("No Movement to print.\n");
    return;
    }

    printf("----- Movement #%d -----\n", movement->id);
    printf("Name            : %s\n", movement->name);
    printf("Type            : %s\n", TypeNames[movement->type]);
    printf("Category        : %s\n", CategoryNames[movement->category]);
    printf("Status          : %s\n", StatusNames[movement->status]);
    printf("Status Chance   : %d%%\n", movement->statusaccuracy);
    printf("Power           : %d\n", movement->power);
    printf("Accuracy        : %d%%\n", movement->accuracy);
    printf("-------------------------\n");
}