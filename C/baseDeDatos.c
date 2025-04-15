#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include "baseDeDatos.h"

#define MAX_LEN 50
#define MAX_ITEMS 100

int cargar_pokemons(sqlite3 *db, Pokemon *pokemons, int max) {
    printf("Preparando consulta de Pokemons...\n");
    const char *sql = "SELECT * FROM Pokemon";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int i = 0;

    if (rc != SQLITE_OK) {
        printf("Error preparando consulta de Pokemons: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    printf("Consulta preparada correctamente. Leyendo filas...\n");

    while (sqlite3_step(stmt) == SQLITE_ROW && i < max) {
        pokemons[i].id = sqlite3_column_int(stmt, 0);
    
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *type1 = sqlite3_column_text(stmt, 2);
        const unsigned char *type2 = sqlite3_column_text(stmt, 3);
    
        strncpy(pokemons[i].name, name ? (const char *)name : "NULL", MAX_LEN);
        strncpy(pokemons[i].type1, type1 ? (const char *)type1 : "NULL", MAX_LEN);
        strncpy(pokemons[i].type2, type2 ? (const char *)type2 : "NULL", MAX_LEN);
    
        pokemons[i].PS = sqlite3_column_int(stmt, 4);
        pokemons[i].ataque = sqlite3_column_int(stmt, 5);
        pokemons[i].defensa = sqlite3_column_int(stmt, 6);
        pokemons[i].ataqueESP = sqlite3_column_int(stmt, 7);
        pokemons[i].defensaESP = sqlite3_column_int(stmt, 8);
        pokemons[i].velocidad = sqlite3_column_int(stmt, 9);
    
        printf("Fila %d: %s (%d PS)\n", i + 1, pokemons[i].name, pokemons[i].PS);
        i++;
    }
    

    printf("Leídas %d filas de Pokémon.\n", i);
    sqlite3_finalize(stmt);
    return i;
}

int cargar_jugadores(sqlite3 *db, Jugador *jugadores, int max) {
    const char *sql = "SELECT * FROM Jugador";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int i = 0;

    if (rc != SQLITE_OK) {
        printf("Error preparando consulta de Pokemons: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW && i < max) {
        jugadores[i].id = sqlite3_column_int(stmt, 0);
    
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *password = sqlite3_column_text(stmt, 2);
        const unsigned char *genero = sqlite3_column_text(stmt, 3);
    
        strncpy(jugadores[i].name, name ? (const char *)name : "NULL", MAX_LEN);
        strncpy(jugadores[i].password, password ? (const char *)password : "NULL", MAX_LEN);
        strncpy(jugadores[i].genero, genero ? (const char *)genero : "NULL", MAX_LEN);
    
        jugadores[i].dinero = sqlite3_column_int(stmt, 4);
        jugadores[i].maxLVL = sqlite3_column_int(stmt, 5);
    
        printf("Jugador %d: %s (Dinero: %d)\n", i + 1, jugadores[i].name, jugadores[i].dinero);
        i++;
    }

    sqlite3_finalize(stmt);
    return i;
}

int cargar_objetos(sqlite3 *db, Objeto *objetos, int max) {
    const char *sql = "SELECT * FROM Objeto";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int i = 0;

    if (rc != SQLITE_OK) {
        printf("Error preparando consulta de Pokemons: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW && i < max) {
        objetos[i].id = sqlite3_column_int(stmt, 0);
    
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        strncpy(objetos[i].name, name ? (const char *)name : "NULL", MAX_LEN);
    
        objetos[i].cura = sqlite3_column_int(stmt, 2);
        objetos[i].revivir = sqlite3_column_int(stmt, 3);
        objetos[i].captura = sqlite3_column_int(stmt, 4);
        objetos[i].subida = sqlite3_column_int(stmt, 5);
    
        printf("Objeto %d: %s (Cura: %d)\n", i + 1, objetos[i].name, objetos[i].cura);
        i++;
    }
    

    sqlite3_finalize(stmt);
    return i;
}

int cargar_movimientos(sqlite3 *db, Movimiento *movs, int max) {
    const char *sql = "SELECT * FROM Movimiento";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int i = 0;

    if (rc != SQLITE_OK) {
        printf("Error preparando consulta de Pokemons: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW && i < max) {
        movs[i].id = sqlite3_column_int(stmt, 0);
        movs[i].idTipo = sqlite3_column_int(stmt, 1);
        movs[i].idCategoriaMov = sqlite3_column_int(stmt, 2);
    
        const unsigned char *name = sqlite3_column_text(stmt, 3);
        strncpy(movs[i].name, name ? (const char *)name : "NULL", MAX_LEN);
    
        movs[i].potencia = sqlite3_column_int(stmt, 4);
        movs[i].precision = sqlite3_column_int(stmt, 5);
        movs[i].prioridad = sqlite3_column_int(stmt, 6);
    
        printf("Movimiento %d: %s (Potencia: %d)\n", i + 1, movs[i].name, movs[i].potencia);
        i++;
    }
    

    sqlite3_finalize(stmt);
    return i;
}

int insertar_jugador(sqlite3 *db, int id, const char *name, const char *password, const char *genero, int dinero, int maxLVL, Jugador *jugadores, int max) {
    const char *sql = "INSERT INTO Jugador (id, name, password, genero, dinero, maxLVL) VALUES (?, ?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando inserción de jugador: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Asignamos parámetros
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, password, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, genero, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, dinero);
    sqlite3_bind_int(stmt, 6, maxLVL);

    // Ejecutamos
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error insertando jugador: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    printf("Jugador insertado correctamente.\n");

    sqlite3_finalize(stmt);

    // Recargar jugadores
    cargar_jugadores(db, jugadores, max);

    return 1;
}
