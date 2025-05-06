#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pokemon.h"
#include "movement.h"

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
    printf("Evolves at LvL : %d\n",    pokemon->evolvl);
    printf("-----------------------\n");
}

PokemonPlayer* createPokemonPlayer(Pokemon* pokemon, int pokeid, char nickname[], Movement listMovement[4], int xp, int curHp, Status status) {
    PokemonPlayer *pokemonplayer = malloc(sizeof *pokemonplayer);
    if (!pokemonplayer) {
        return NULL;
    }

    pokemonplayer->pokemon = pokemon;
    pokemonplayer->pokeid  = pokeid;
    pokemonplayer->xp      = xp;
    pokemonplayer->curHp   = curHp;
    pokemonplayer->status  = status;

    strncpy(pokemonplayer->nickname, nickname, sizeof pokemonplayer->nickname - 1);
    pokemonplayer->nickname[sizeof pokemonplayer->nickname - 1] = '\0';

    for (int i = 0; i < 4; ++i) {
        pokemonplayer->listMovement[i] = listMovement[i];
    }

    return pokemonplayer;
}

void printPokemonPlayer(const PokemonPlayer *pokemonplayer) {
    if (!pokemonplayer) {
        printf("No PokemonPlayer to print.\n");
        return;
    }

    printf("===== PokemonPlayer #%d =====\n", pokemonplayer->pokeid);
    printPokemon(pokemonplayer->pokemon);
    printf("Nickname      : %s\n", pokemonplayer->nickname);
    printf("XP            : %d\n", pokemonplayer->xp);
    printf("Current HP    : %d\n", pokemonplayer->curHp);
    printf("Status        : %s\n", StatusNames[pokemonplayer->status]);

    for (int i = 0; i < 4; ++i) {
    printf("--- Movement slot %d ---\n", i + 1);
    printMovement(&pokemonplayer->listMovement[i]);
    }
    printf("============================\n");
}