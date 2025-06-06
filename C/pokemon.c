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

    pokemon->type[0] = (Type) type1;
    pokemon->type[1] = (Type) type2;

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
    printf("Type 1         : %s\n",    getTypeName((Type) pokemon->type[0]));
    printf("Type 2         : %s\n",    getTypeName((Type) pokemon->type[1]));
    printf("Evolves at LvL : %d\n",    pokemon->evolvl);
    printf("-----------------------\n");
}

void printPokemonSmall(Pokemon* pokemon) {
    if (!pokemon) {
        printf("No Pokemon to print.\n");
        return;
    }

    printf("Name           : %s\n",    pokemon->name);
}

PokemonPlayer* createPokemonPlayer(Pokemon* pokemon, int pokeid, char nickname[], Movement** listMovement, int listMovementSize, int xp, int curHp, Status status) {
    PokemonPlayer *pokemonplayer = malloc(sizeof *pokemonplayer);
    if (!pokemonplayer) {
        return NULL;
    }

    pokemonplayer->pokemon          = pokemon;
    pokemonplayer->pokeid           = pokeid;
    pokemonplayer->xp               = xp;
    pokemonplayer->curHp            = curHp;
    pokemonplayer->status           = status;
    pokemonplayer->listMovementSize = listMovementSize;

    // Copy nickname safely
    strncpy(pokemonplayer->nickname, nickname, sizeof pokemonplayer->nickname - 1);
    pokemonplayer->nickname[sizeof pokemonplayer->nickname - 1] = '\0';

    // Allocate memory for listMovement
    pokemonplayer->listMovement = malloc(sizeof(Movement*) * listMovementSize);
    if (!pokemonplayer->listMovement) {
        free(pokemonplayer);
        return NULL;
    }

    // Copy movement pointers
    for (int i = 0; i < listMovementSize; ++i) {
        pokemonplayer->listMovement[i] = listMovement[i];
    }

    return pokemonplayer;
}

void printPokemonPlayer(PokemonPlayer* pokemonplayer) {
    if (!pokemonplayer || pokemonplayer == NULL || pokemonplayer == 0) {
        printf("No PokemonPlayer to print.\n");
        return;
    }

    printf("===== PokemonPlayer #%d =====\n", pokemonplayer->pokeid);
    printPokemon(pokemonplayer->pokemon);
    printf("Nickname      : %s\n", pokemonplayer->nickname);
    printf("XP            : %d\n", pokemonplayer->xp);
    printf("Current HP    : %d\n", pokemonplayer->curHp);
    printf("Status        : %s\n", getStatusName((Status) pokemonplayer->status));

    for (int i = 0; i < pokemonplayer->listMovementSize; ++i) {
        printf("--- Movement slot %d ---\n", i + 1);
        printMovement(pokemonplayer->listMovement[i]);
    }
    printf("============================\n");
}

void printPokemonPlayerSmall(PokemonPlayer* pokemonplayer) {
    if (!pokemonplayer || pokemonplayer == NULL || pokemonplayer == 0) {
        printf("No PokemonPlayer to print.\n");
        return;
    }

    printf("===== PokemonPlayer #%d =====\n", pokemonplayer->pokeid);
    printPokemonSmall(pokemonplayer->pokemon);
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

int calculateAttackDamage(PokemonPlayerBattle* attackPokemon, PokemonPlayerBattle* defensePokemon, Movement* movement) {
    if (!attackPokemon || !defensePokemon || !movement) {
        fprintf(stderr, "Error: Null pointer passed to calculateAttackDamage\n");
        return 0;
    }

    // STATUS moves do no damage
    if (movement->status == STATUS) {
        return 0;
    }

    int baseDamage = (((2 * attackPokemon->lvl) / 5) + 2) * movement->power;

    // Avoid division by zero
    float attackStat, defenseStat;
    if (movement->status == PHYSICAL) {
        attackStat = (float)attackPokemon->battleAttack;
        defenseStat = (float)(defensePokemon->battleDefense == 0 ? 1 : defensePokemon->battleDefense);
    } else { // SPECIAL
        attackStat = (float)attackPokemon->battleSpattack;
        defenseStat = (float)(defensePokemon->battleSpdefense == 0 ? 1 : defensePokemon->battleSpdefense);
    }

    float modifier = attackStat / defenseStat;
    float damage = (baseDamage * modifier) / 50.0f + 2;

    // STAB (Same-Type Attack Bonus)
    int type1 = attackPokemon->pokemonPlayer->pokemon->type[0];
    int type2 = attackPokemon->pokemonPlayer->pokemon->type[1];
    if (movement->type == type1 || movement->type == type2) {
        damage *= 1.5f;
    }

    // Random factor: between 85% and 100%
    float randModifier = (85 + rand() % 16) / 100.0f;
    damage *= randModifier;

    // Critical hit: 1/24 chance
    if ((rand() % 24) == 0) {
        damage *= 2;
        printf("Critical Hit!\n");
    }

    return (int)damage;
}


void combatAttack(PokemonPlayerBattle* attackPokemon, PokemonPlayerBattle* defensePokemon, Movement* movement) {
    int hitChance = rand() % 100;
    if (hitChance >= movement->accuracy) {
        printf("El movimiento fallo!\n");
        return;
    }
    
    int totalDamage = calculateAttackDamage(attackPokemon, defensePokemon, movement);
    double typeEffectiveness = effectiveness(movement->type, defensePokemon->pokemonPlayer->pokemon->type[0], defensePokemon->pokemonPlayer->pokemon->type[1]);
    defensePokemon->pokemonPlayer->curHp -= (totalDamage * typeEffectiveness);
    if (defensePokemon->pokemonPlayer->curHp < 0) defensePokemon->pokemonPlayer->curHp = 0;

    printf("%s hizo %d de danyo! (Efectividad: %.2fx)\n", attackPokemon->pokemonPlayer->nickname, (int) (totalDamage * typeEffectiveness), typeEffectiveness);
}