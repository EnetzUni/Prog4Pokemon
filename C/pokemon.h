#ifndef POKEMON_H
#define POKEMON_H

#include "type.h"

typedef struct {
        /// The Pokedex number for the Pokemon.
        int id;

        /// The name of the Pokemon.
        char name[255];

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
        Type type;

        /// The level at which the Pokemon evolves.
        int evolvl;
} Pokemon;

#endif