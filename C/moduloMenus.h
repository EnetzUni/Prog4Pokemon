#ifndef MODULOMENUS_H_
#define MODULOMENUS_H_

void presentacion(sqlite3 *db);

void menuLoginRegistro(sqlite3 *db);

void menuRegistro(sqlite3 *db);

void menuLogin(sqlite3 *db);

void menuErrorLoginRegistro(int caseMenu);

void menuPrincipal(sqlite3 *db);

#endif