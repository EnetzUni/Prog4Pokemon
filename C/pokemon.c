#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
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

PokemonPlayer* createPokemonPlayer(Pokemon* pokemon, int pokeid, char nickname[], Movement* listMovement[4], int listMovementSize, int xp, int curHp, Status status) {
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

    for (int i = 0; i < pokemonplayer->listMovementSize; ++i) {
        pokemonplayer->listMovement[i] = listMovement[i];
    }

    return pokemonplayer;
}

void printPokemonPlayer(PokemonPlayer* pokemonplayer) {
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

    for (int i = 0; i < pokemonplayer->listMovementSize; ++i) {
    printf("--- Movement slot %d ---\n", i + 1);
    printMovement(pokemonplayer->listMovement[i]);
    }
    printf("============================\n");
}

int calculateLvl(int xp) {
    return (int) cbrt(xp);
}

int calculateBattleHp(int hp, int lvl) {
    return (int) ((((2 * hp + 94.75) * lvl) / 100) + lvl + 10);
}

int calculateBattleStats(int stat, int lvl) {
    return (int) (((((2 * stat + 94.75) * lvl) / 100) + 5) * 1.1);
}

PokemonPlayerBattle* createPokemonPlayerBattle(PokemonPlayer* pokemonPlayer) {
    PokemonPlayerBattle* pokemonPlayerBattle = malloc(sizeof* pokemonPlayerBattle);
    if (!pokemonPlayerBattle) {
        return NULL;
    }

    pokemonPlayerBattle->pokemonPlayer   = pokemonPlayer;
    pokemonPlayerBattle->lvl             = calculateLvl(pokemonPlayer->xp);
    pokemonPlayerBattle->battleHp        = calculateBattleHp(pokemonPlayer->pokemon->hp, pokemonPlayerBattle->lvl);
    pokemonPlayerBattle->battleAttack    = calculateBattleStats(pokemonPlayer->pokemon->attack, pokemonPlayerBattle->lvl);
    pokemonPlayerBattle->battleDefense   = calculateBattleStats(pokemonPlayer->pokemon->defense, pokemonPlayerBattle->lvl);
    pokemonPlayerBattle->battleSpattack  = calculateBattleStats(pokemonPlayer->pokemon->spattack, pokemonPlayerBattle->lvl);
    pokemonPlayerBattle->battleSpdefense = calculateBattleStats(pokemonPlayer->pokemon->spdefense, pokemonPlayerBattle->lvl);
    pokemonPlayerBattle->battleSpeed     = calculateBattleStats(pokemonPlayer->pokemon->speed, pokemonPlayerBattle->lvl);

    return pokemonPlayerBattle;
}

void printPokemonPlayerBattle(PokemonPlayerBattle* pokemonPlayerBattle) {
    if (!pokemonPlayerBattle || !pokemonPlayerBattle->pokemonPlayer) {
        printf("No PokemonPlayerBattle to print.\n");
        return;
    }

    printf("===== PokemonPlayerBattle =====\n");
    printPokemonPlayer(pokemonPlayerBattle->pokemonPlayer);
    printf("Level            : %d\n", pokemonPlayerBattle->lvl);
    printf("Battle HP        : %d\n", pokemonPlayerBattle->battleHp);
    printf("Battle Attack    : %d\n", pokemonPlayerBattle->battleAttack);
    printf("Battle Defense   : %d\n", pokemonPlayerBattle->battleDefense);
    printf("Battle Sp. Attack: %d\n", pokemonPlayerBattle->battleSpattack);
    printf("Battle Sp. Def.  : %d\n", pokemonPlayerBattle->battleSpdefense);
    printf("Battle Speed     : %d\n", pokemonPlayerBattle->battleSpeed);
    printf("===============================\n");
}