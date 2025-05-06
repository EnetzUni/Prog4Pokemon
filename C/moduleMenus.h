#ifndef MODULEMENUS_H_
#define MODULEMENUS_H_

#include "db.h"

void presentation(sqlite3 *db);

void menuLoginRegister(sqlite3 *db);

void menuRegister(sqlite3 *db);

void menuLogin(sqlite3 *db);

void menuErrorLoginRegister(int caseMenu);

void menuPrincipal(sqlite3 *db);

void imprimirTexto(char* texto);

#endif