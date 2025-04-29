#ifndef MODULEMENUS_H_
#define MODULEMENUS_H_

#include "baseDeDatos.h"

void presentation(sqlite3 *db, Jugador *jugadores);

void menuLoginRegister(sqlite3 *db, Jugador *jugadores);

void menuRegister(sqlite3 *db, Jugador *jugadores);

void menuLogin(sqlite3 *db, Jugador *jugadores);

void menuErrorLoginRegister(int caseMenu);

void menuPrincipal(sqlite3 *db, Jugador *jugadores);

#endif