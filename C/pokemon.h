#ifndef POKEMON_H
#define POKEMON_H

#include "type.h"
#include "status.h"
#include "movement.h"

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
        Type type[2];

        /// The level at which the Pokemon evolves.
        int evolvl;
} Pokemon;

typedef struct {
        // The Pokemon species.
        Pokemon* pokemon;

        /// The Pokemon's pokeid.
        int pokeid;

        /// The Pokemon's nickname.
        char nickname[255];

        /// The Pokemon's list of Movements.
        Movement listMovement[4];

        /// The Pokemon's exact amount of xp to calculate level.
        int xp;

        /// The Pokemon's current hit points.
        int curHp;

        /// The Pokemon's current status
        Status status;
} PokemonPlayer;

Pokemon* createPokemon(int, char[], int, int, int, int, int, int, Type, Type, int);

void printPokemon(Pokemon*);

PokemonPlayer* createPokemonPlayer(Pokemon*, int, char[], Movement[4], int, int, Status);

void printPokemonPlayer(const PokemonPlayer*);

#endif