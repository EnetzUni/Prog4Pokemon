#include <stdio.h>
#include "moduleMenus.h"
#include "db.h"

void readConfig(char* pathDB, char* nicknameAdmin, const char* fichero) {
    FILE* archivo = fopen(fichero, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo de configuracion.\n");
        return;
    }

    int index = 0;
    char c = fgetc(archivo);

    // Leer primera línea: pathDB
    while (c != '\n' && c != EOF) {
        pathDB[index++] = c;
        c = fgetc(archivo);
    }
    pathDB[index] = '\0';

    // Leer segunda línea: nicknameAdmin
    index = 0;
    c = fgetc(archivo);  // Avanzar al primer carácter de la segunda línea
    while (c != '\n' && c != EOF) {
        nicknameAdmin[index++] = c;
        c = fgetc(archivo);
    }
    nicknameAdmin[index] = '\0';

    fclose(archivo);
}


int main(void)
{
    printf("Inicio del programa\n");

    // Leer el fichero de configuracion
    char pathDB[256];
    char nicknameAdmin[100];

    readConfig(pathDB, nicknameAdmin, "./config.txt");

    sqlite3* db;
    printf("Intentando abrir la base de datos...\n");
    
    if (sqlite3_open(pathDB, &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    printf("Base de datos abierta correctamente\n");

    sqlite3_soft_heap_limit64(0);
    //initializeDb(db);

    presentation(db, nicknameAdmin);

    sqlite3_close(db);
    return 0;
}