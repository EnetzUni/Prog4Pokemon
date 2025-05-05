#include "pokemon.h"

void printPokemon(const Pokemon* pokemon) {
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