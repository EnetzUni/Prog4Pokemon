#ifndef MODULEMENUS_H_
#define MODULEMENUS_H_

#include "db.h"

void presentation(sqlite3 *db, Player *players);

void menuLoginRegister(sqlite3 *db, Player *players);

void menuRegister(sqlite3 *db, Player *players);

void menuLogin(sqlite3 *db, Player *players);

void menuErrorLoginRegister(int caseMenu);

void menuPrincipal(sqlite3 *db, Player *players);

void imprimirTexto(char* texto);

#endif