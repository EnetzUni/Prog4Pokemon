#ifndef DB_H
#define DB_H

#include "sqlite3.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"

// Funciones para obtener datos
int cargar_pokemons(sqlite3 *db, Pokemon *pokemons, int max);
int cargar_jugadores(sqlite3 *db, Player *jugadores, int max);
int cargar_movimientos(sqlite3 *db, Movement *movs, int max);
int insertar_jugador(sqlite3 *db, const char *name, const char *password, bool gender, int maxLVL, int story);


#endif