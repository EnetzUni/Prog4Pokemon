#ifndef DB_H
#define DB_H

#include "sqlite3.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"

// Funciones para obtener datos
Pokemon* loadPokemon(sqlite3*, int);

/*int cargar_pokemons(sqlite3 *db, Pokemon *pokemons, int max);
int cargar_jugadores(sqlite3 *db, Player *jugadores, int max);
int cargar_movimientos(sqlite3 *db, Movement *movs, int max);
int insertar_jugador(sqlite3 *db, int id, const char *name, const char *password, const char *genero, int dinero, int maxLVL, Player *jugadores, int max);*/


#endif