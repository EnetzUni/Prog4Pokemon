#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#pragma once

#include <iostream>
#include "type.h"
#include "category.h"
#include "status.h"

/** 
 * @class Movement
 * @brief This is the Movement class, with each movement's stats.
 */
class Movement {
public:

    /// Unique identifier for the move.
    int id;

    /// Name of the move.
    string name;

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
};

#endif