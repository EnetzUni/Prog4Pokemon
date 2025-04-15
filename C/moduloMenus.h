#ifndef MODULOMENUS_H_
#define MODULOMENUS_H_

void presentacion(sqlite3 *db, Jugador *jugadores);

void menuLoginRegistro(sqlite3 *db, Jugador *jugadores);

void menuRegistro(sqlite3 *db, Jugador *jugadores);

void menuLogin(sqlite3 *db, Jugador *jugadores);

void menuErrorLoginRegistro(int caseMenu);

void menuPrincipal(sqlite3 *db, Jugador *jugadores);

#endif