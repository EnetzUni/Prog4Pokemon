#ifndef DB_H
#define DB_H

#include "sqlite3.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"

// Funciones para obtener datos
Pokemon* loadPokemon(sqlite3* db, int id);

int cargar_pokemons(sqlite3 *db, Pokemon *pokemons, int max);
int loadPlayer(sqlite3 *db, Player *jugadores, int max);
int cargar_movimientos(sqlite3 *db, Movement *movs, int max);
int insertPlayer(sqlite3 *db, const char *name, const char *password, bool gender, int maxLVL, int story);


#endif