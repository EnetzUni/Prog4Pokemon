#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "type.h"
#include "category.h"
#include "status.h"
#include "sqlite3.h"

typedef struct {
    /// Unique identifier for the move.
    int id;

    /// Name of the move.
    char name[255];

    /// Elemental type of the move.
    Type type;

    /// The category of the move: Physical, Special, or Status.
    Category category;

    /// The status condition this move may inflict.
    Status status;

    /// The chance (in %) for the status condition to be applied.
    int statusaccuracy;

    /// The base power of the move.
    int power;

    /// The chance (in %) for the move to successfully hit the target.
    int accuracy;
} Movement;

Movement* createMovement(int, char[], Type, Category, Status, int, int, int);

void printMovement(Movement* movement);

void printMovementSmall(Movement* movement);

Movement** createRandomMovementList(sqlite3* db);
#endif