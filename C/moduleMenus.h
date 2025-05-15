#ifndef MODULEMENUS_H_
#define MODULEMENUS_H_

#include "db.h"

void imprimirTexto(char* texto);

void presentation(sqlite3 *db);

void menuLoginRegister(sqlite3 *db);

void menuRegister(sqlite3 *db);

void menuLogin(sqlite3 *db);

void menuPrincipal(sqlite3 *db, Player *player);

void menuPC(sqlite3 *db);

#endif