#ifndef DB_H
#define DB_H

#include "sqlite3.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"

// Funciones para obtener datos
Pokemon* loadPokemon(sqlite3*, int);
int checkPlayer(sqlite3*, char[]);

int cargar_pokemons(sqlite3 *db, Pokemon *pokemons, int max);
int loadPlayer(sqlite3 *db, Player *jugadores, int max);
int checkPassword(sqlite3* db, char* nickname, char* password);
int cargar_movimientos(sqlite3 *db, Movement *movs, int max);
int insertPlayer(sqlite3 *db, char *name, char *password, bool gender, int maxLVL, int story);

#endif