#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include "db.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"
#include "type.h"

Pokemon* loadPokemon(sqlite3* db, int id) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM Pokemon WHERE id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind ID: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return NULL;
    }

	printf("SQL query prepared (SELECT)\n");

    Pokemon* pokemon;
	char name[255];
    int hp;
    int attack;
    int defense;
    int spattack;
    int spdefense;
    int speed;
    Type type[2];
    int evolvl;

	printf("Showing Pokemon:\n");

    if (sqlite3_step(stmt) == SQLITE_ROW) {
		strcpy(name, (char *) sqlite3_column_text(stmt, 1));
        hp = sqlite3_column_int(stmt, 2);
        attack = sqlite3_column_int(stmt, 3);
        defense = sqlite3_column_int(stmt, 4);
        spattack = sqlite3_column_int(stmt, 5);
        spdefense = sqlite3_column_int(stmt, 6);
        speed = sqlite3_column_int(stmt, 7);
		type[0] = (Type) sqlite3_column_int(stmt, 8);
        type[1] = (Type) sqlite3_column_int(stmt, 9);
        evolvl = sqlite3_column_int(stmt, 10);
	}

    pokemon = (Pokemon*) createPokemon(id, name, hp, attack, defense, spattack, spdefense, speed, type[0], type[1], evolvl);
    printPokemon(pokemon);

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Pokemon*) NULL;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return (Pokemon*) pokemon;
}

int checkPlayer(sqlite3* db, char* nickname) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT CASE WHEN COUNT(*) FILTER (WHERE nickname = ?) > 0 THEN 1 ELSE 0 END AS exists FROM Player;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (sqlite3_bind_text(stmt, 1, nickname, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind nickname: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    int exists = 0;
    if (rc == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0);
    }

    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        fprintf(stderr, "Failed to finalize statement: %s\n", sqlite3_errmsg(db));
    }

    return exists;
}

/*int cargar_pokemons(sqlite3* db, Pokemon* pokemons, int max) {
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
*/
int cargar_jugadores(sqlite3 *db, Player *jugadores, int max) {
    const char *sql = "SELECT * FROM Player";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    int i = 0;

    if (rc != SQLITE_OK) {
        printf("Error preparando consulta de Player: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW && i < max) {
        jugadores[i].id = sqlite3_column_int(stmt, 0);
    
        const unsigned char *name = sqlite3_column_text(stmt, 1);
        const unsigned char *password = sqlite3_column_text(stmt, 2);  
    
        strncpy(jugadores[i].name, name ? (const char *)name : "NULL", MAX_LEN);
        strncpy(jugadores[i].password, password ? (const char *)password : "NULL", MAX_LEN);
    
        jugadores[i].genero = sqlite3_column_int(stmt, 3) != 0;
        jugadores[i].maxLVL = sqlite3_column_int(stmt, 4);
        jugadores[i].story = sqlite3_column_int(stmt, 5);
    
        printf("Jugador %d: %s (Dinero: %d)\n", i + 1, jugadores[i].name, jugadores[i].dinero);
        i++;
    }

    sqlite3_finalize(stmt);
    return i;
}
/*
int cargar_movimientos(sqlite3 *db, Movement *movs, int max) {
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

*/

int insertPlayer(sqlite3 *db, const char *name, const char *password, bool gender, int maxLVL, int story) {
    const char *sql = "INSERT INTO Player (name, password, gender, maxLVL, story) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando inserción de Player: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Asignamos parámetros
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, (int)gender);
    sqlite3_bind_int(stmt, 4, maxLVL);
    sqlite3_bind_int(stmt, 5, story);

    // Ejecutamos
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error insertando Player: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    printf("Player insertado correctamente.\n");

    sqlite3_finalize(stmt);

    // Recargar jugadores
    cargar_jugadores(db, jugadores, max);

    return 1;
}
