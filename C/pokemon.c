#include <stdlib.h>    // for malloc, free
#include <string.h>    // for strncpy
#include <stdio.h>     // for NULL
#include "Pokemon.h"

Pokemon* createPokemon(int id, char name[], int hp, int attack, int defense, int spattack, int spdefense, int speed, Type type1, Type type2, int evolvl) {
    Pokemon* pokemon = malloc(sizeof* pokemon);
    if (pokemon == NULL) {
        return NULL;
    }

    pokemon->id        = id;
    pokemon->hp        = hp;
    pokemon->attack    = attack;
    pokemon->defense   = defense;
    pokemon->spattack  = spattack;
    pokemon->spdefense = spdefense;
    pokemon->speed     = speed;
    pokemon->evolvl    = evolvl;

    pokemon->type[0] = type1;
    pokemon->type[1] = type2;

    strncpy(pokemon->name, name, sizeof pokemon->name - 1);
    pokemon->name[sizeof pokemon->name - 1] = '\0';

    return pokemon;
}

void printPokemon(Pokemon* pokemon) {
    if (!pokemon) {
        printf("No Pokemon to print.\n");
        return;
    }

    printf("----- Pokemon #%d -----\n", pokemon->id);
    printf("Name           : %s\n",    pokemon->name);
    printf("HP             : %d\n",    pokemon->hp);
    printf("Attack         : %d\n",    pokemon->attack);
    printf("Defense        : %d\n",    pokemon->defense);
    printf("Sp. Attack     : %d\n",    pokemon->spattack);
    printf("Sp. Defense    : %d\n",    pokemon->spdefense);
    printf("Speed          : %d\n",    pokemon->speed);
    printf("Type 1         : %s\n",    TypeNames[pokemon->type[0]]);
    printf("Type 2         : %s\n",    TypeNames[pokemon->type[1]]);
    printf("Evolves at Lvl : %d\n",    pokemon->evolvl);
    printf("-----------------------\n");
}