#ifndef MODULEMENUS_H_
#define MODULEMENUS_H_

#include "db.h"

#ifdef __cplusplus
extern "C" {
#endif

void imprimirTexto(char* texto);

void presentation(sqlite3 *db, char* nicknameAdmin);

void menuLoginRegister(sqlite3 *db, char* nicknameAdmin);

void menuRegister(sqlite3 *db, char* nicknameAdmin);

void menuLogin(sqlite3 *db, char* nicknameAdmin);

void menuPrincipal(sqlite3 *db, Player* player);

void menuPC(sqlite3 *db, Player* player);

void combate(sqlite3 *db, Player* player);

#ifdef __cplusplus
}
#endif

#endif // MODULEMENUS_H_
