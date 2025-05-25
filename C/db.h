#ifndef DB_H
#define DB_H

#include "sqlite3.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"
#include "pc.h"

#ifdef __cplusplus
extern "C" {
#endif

// Functions of the Database

// Load a Pokemon using its id
Pokemon* loadPokemon(sqlite3*, int);

// Load a PokemonPlayer using its id
PokemonPlayer* loadPokemonPlayer(sqlite3*, int);

// Load the movements for a PokemonPlayer, with the id of the PokemonPlayer and an int* to return the count of movements
Movement** loadPokemonPlayerMovement(sqlite3*, int, int*);

// Check if a Player exists using its nickname
int checkPlayer(sqlite3*, char*);

// Check if a Player's nickname and password are correct to log in
int checkPassword(sqlite3*, char*, char*);

// Load a Movement using its id
Movement* loadMovement(sqlite3*, int);

// Load a Player using its nickname
Player* loadPlayer(sqlite3*, char*);

// Load the PokemonPlayer in the team for a Player, with the id of the Player and an int* to return the count of PokemonPlayer
PokemonPlayer** loadPlayerPokemonPlayer(sqlite3*, char*, int*);

// Insert a Player into the database
int insertPlayer(sqlite3*, Player*);

// Load the Pc with the PokemonPlayer
PC* loadPc(sqlite3*, char*);

// Load the count of PokemonPlayer in the Pc
int* loadPcCount(sqlite3*, char*);

// Delete the PokemonPlayer in the Player from the Team Table
int deletePlayerTeam(sqlite3* db, Player* player);

// Insert the PokemonPlayer in the Player into the Team Table
int insertPlayerTeam(sqlite3* db, Player* player);

// Insert PokemonPlayer into the DataBase
int insertPokemonPlayer(sqlite3* db, PokemonPlayer* pokemon);

// Insert the PC into the DataBase
int insertPc(sqlite3* db, PC* pc);

// Create admin for DataBase.
void initializeDb(sqlite3* db);

#ifdef __cplusplus
}
#endif

#endif // DB_H