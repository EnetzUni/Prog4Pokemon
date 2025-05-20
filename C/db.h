#ifndef DB_H
#define DB_H

#include "sqlite3.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"

// Funciones para obtener datos
Pokemon* loadPokemon(sqlite3*, int);
PokemonPlayer* loadPokemonPlayer(sqlite3*, int);
Movement** loadPokemonPlayerMovement(sqlite3*, int, int*);
int checkPlayer(sqlite3*, char*);
int checkPassword(sqlite3*, char*, char*);
Movement* loadMovement(sqlite3*, int);
Player* loadPlayer(sqlite3*, char*);
int insertPlayer(sqlite3* db, char* nickname, char* password, bool gender, int maxLVL, int story);

#endif