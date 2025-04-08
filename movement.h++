#pragma once

#include <iostream>
#include "type.h++"
#include "status.h++"
using namespace std;

/** 
 * @class Movement
 * @brief This is the Movement class, with each movement's stats.
 */
class Movement {
public:
    /** 
     * @enum Category
     * @brief Represents the category of the move.
     *
     * - PHYSICAL: The category of the attack is Physical, it uses Attack and Defense.
     * - SPECIAL: The category of the attack is Special, it uses Special Attack and Special Defense.
     * - STATUS: Non-damaging moves that apply effects.
     */
	enum class Category { 
        PHYSICAL, SPECIAL, STATUS 
    };

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
