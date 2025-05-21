#ifndef DB_H
#define DB_H

#include "sqlite3.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"

// Functions of the Database

// Load a Pokemon using it's id
Pokemon* loadPokemon(sqlite3*, int);

// Load a PokemonPlayer using it's id
PokemonPlayer* loadPokemonPlayer(sqlite3*, int);

// Load the movements for a PokemonPlayer, with the id of the PokemonPlayer and an int* to return the count of movements
Movement** loadPokemonPlayerMovement(sqlite3*, int, int*);

// Check if a Player exists using it's nickname
int checkPlayer(sqlite3*, char*);

// Check if a Player's exists using it's nickname and password are correct to log in
int checkPassword(sqlite3*, char*, char*);

// Load a Movement using it's id
Movement* loadMovement(sqlite3*, int);

// Load a Movement using it's nickname
Player* loadPlayer(sqlite3*, char*);

// Load the PokemonPlayer in the team for a Player, with the id of the Player and an int* to return the count of PokemonPlayer
PokemonPlayer** loadPlayerPokemonPlayer(sqlite3*, int, int*);

// Insert a Player into the database
int insertPlayer(sqlite3*, Player*);

#endif