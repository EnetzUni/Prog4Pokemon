#pragma once

#include <iostream>
#include <vector>
#include "type.h++"
#include "movement.h++"
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

        /// The base attack stat of the Pokemon.
        int attack;

        /// The base defense stat of the Pokemon.
        int defense;

        /// The base special attack stat of the Pokemon.
        int spattack;

        /// The base special defense stat of the Pokemon.
        int spdefense;

        /// The base speed stat of the Pokemon.
        int speed;

        /// The list of types of the Pokemon (1 or 2 types)
        vector<Type> type;
};

class PokemonPlayer : public Pokemon {
    public:
        /// The Pokemon's nickname.
        string nickname;

        /// The Pokemon's list of Movements.
        vector<Movement> listMovement;

        /// The Pokemon's level.
        int lvl;

        /// The Pokemon's exact amount of xp to calculate level.
        int xp;

        /// The hit points of the Pokemon according to their current level.
        int lvlhp;
        
        /// The attack stat of the Pokemon according to their current level.
        int lvlattack;

        /// The defense stat of the Pokemon according to their current level.
        int lvldefense;

        /// The special attack stat of the Pokemon according to their current level.
        int lvlspattack;

        /// The special defense stat of the Pokemon according to their current level.
        int lvlspdefense;

        /// The speed stat of the Pokemon according to their current level.
        int lvlspeed;

        /// The Pokemon's current hit points.
        int curHp;

        /// The Pokemon's current status
        Status status;
};

void xptolvl(int);