#pragma once

#include <iostream>
#include <vector>
#include "type.h++"
using namespace std;

/** 
 * @class Pokemon
 * @brief This is the main Pokemon class, with base stats.
 */
class Pokemon {
    public:
        /// The Pokedex number for the Pokemon.
        int id;

        /// The name of the Pokemon.
        string name;

        /// The base hit points of the Pokemon.
        int hp;

        /// The attack stat of the Pokemon.
        int attack;

        /// The defense stat of the Pokemon.
        int defense;

        /// The special attack stat of the Pokemon.
        int spattack;

        /// The special defense stat of the Pokemon.
        int spdefense;

        /// The speed stat of the Pokemon.
        int speed;

        /// The list of types of the Pokemon (1 or 2 types)
        vector<Type> type;
};
