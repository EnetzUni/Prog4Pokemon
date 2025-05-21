#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "sqlite3.h"
#include "db.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"
#include "type.h"

Pokemon* loadPokemon(sqlite3* db, int id) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT p.id, p.name, p.hp, p.attack, p.defense, p.spattack, p.spdefense, p.speed, p.type1, p.type2, pe.level FROM Pokemon p JOIN PokemonEvolution pe ON pe.idPokemon = p.id WHERE p.id = ?";

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
		type[0] = (Type) (sqlite3_column_int(stmt, 8) - 1);
        type[1] = (Type) (sqlite3_column_int(stmt, 9) - 1);
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

PokemonPlayer* loadPokemonPlayer(sqlite3* db, int id) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT idPokemon, pokeid, nickname, xp, curHp FROM PokemonPlayer WHERE pokeid = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind ID: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return NULL;
    }

    PokemonPlayer* pokemonplayer;
    Pokemon* pokemon;
    int pokeid;
    char nickname[255];
    int* listMovementSize = malloc(sizeof* listMovementSize);
    Movement* listMovement[4] = loadPokemonPlayerMovement(db, id, listMovementSize);
    int xp;
    int curHp;
    Status status;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
		pokemon = loadPokemon(db, sqlite3_column_int(stmt, 1));
        pokeid = sqlite3_column_int(stmt, 2);
        strcpy(nickname, (char*) sqlite3_column_text(stmt, 3));
        xp = sqlite3_column_int(stmt, 4);
        curHp = sqlite3_column_int(stmt, 5);
        status = (Status) (sqlite3_column_int(stmt, 6) - 1);
    }

    pokemonplayer = (PokemonPlayer*) createPokemonPlayer(pokemon, pokeid, nickname, listMovement, *listMovementSize, xp, curHp, status);
    printPokemonPlayer(pokemonplayer);

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (PokemonPlayer*) NULL;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return (PokemonPlayer*) pokemonplayer;
}

Movement** loadPokemonPlayerMovement(sqlite3* db, int id, int* size) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT m1.*, m2.*, m3.*, m4.* FROM PokemonPlayer p LEFT JOIN Movement m1 ON p.move1 = m1.id LEFT JOIN Movement m2 ON p.move2 = m2.id LEFT JOIN Movement m3 ON p.move3 = m3.id LEFT JOIN Movement m4 ON p.move4 = m4.id;";

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

    Movement** movement = malloc(sizeof(*movement) * 4);
    int id;
    char name[255];
    Type type;
    Category category;
    Status status;
    int statusaccuracy;
    int power;
    int accuracy;

	printf("Showing Movement:\n");

    int i = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
		strcpy(name, (char*) sqlite3_column_text(stmt, 1));
        type = (Type) (sqlite3_column_int(stmt, 2) - 1);
        category = (Category) (sqlite3_column_int(stmt, 3) - 1);
        status = (Status) (sqlite3_column_int(stmt, 4) - 1);
        statusaccuracy = sqlite3_column_int(stmt, 5);
        power = sqlite3_column_int(stmt, 6);
        accuracy = sqlite3_column_int(stmt, 7);
        movement[i] = (Movement*) createMovement(id, name, type, category, status, statusaccuracy, power, accuracy);
        printMovement(movement);
        i++;
    }

    *size = i;

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Pokemon*) NULL;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return (Movement**) movement;
}

int checkPlayer(sqlite3* db, char* nickname) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT COUNT(*) FROM Player WHERE nickname = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (sqlite3_bind_text(stmt, 1, nickname, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind nickname: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0) > 0 ? 1 : 0;
    } else {
        fprintf(stderr, "No result returned.\n");
        sqlite3_finalize(stmt);
        return -1;
    }

    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        fprintf(stderr, "Failed to finalize statement: %s\n", sqlite3_errmsg(db));
    }

    return exists;
}

int checkPassword(sqlite3* db, char* nickname, char* password) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT COUNT(*) FROM Player WHERE nickname = ? AND password = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (sqlite3_bind_text(stmt, 1, nickname, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind nickname: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    if (sqlite3_bind_text(stmt, 2, password, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind password: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    int exists = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = sqlite3_column_int(stmt, 0) > 0 ? 1 : 0;
    } else {
        fprintf(stderr, "No result returned.\n");
        sqlite3_finalize(stmt);
        return -1;
    }

    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        fprintf(stderr, "Failed to finalize statement: %s\n", sqlite3_errmsg(db));
    }

    return exists;
}

Movement* loadMovement(sqlite3* db, int id) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM Movement WHERE id = ?";

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

    Movement* movement;
    int id;
    char name[255];
    Type type;
    Category category;
    Status status;
    int statusaccuracy;
    int power;
    int accuracy;

	printf("Showing Pokemon:\n");

    if (sqlite3_step(stmt) == SQLITE_ROW) {
		strcpy(name, (char *) sqlite3_column_text(stmt, 1));
        type = (Type) (sqlite3_column_int(stmt, 2) - 1);
        category = (Category) (sqlite3_column_int(stmt, 3) - 1);
        status = (Status) (sqlite3_column_int(stmt, 4) - 1);
        statusaccuracy = sqlite3_column_int(stmt, 5);
        power = sqlite3_column_int(stmt, 6);
        accuracy = sqlite3_column_int(stmt, 7);
	}

    movement = (Movement*) createMovement(id, name, type, category, status, statusaccuracy, power, accuracy);
    printMovement(movement);

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Pokemon*) NULL;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return (Movement*) movement;
}

Player* loadPlayer(sqlite3* db, char* nickname) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    if (sqlite3_bind_text(stmt, 1, nickname, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind nickname: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return NULL;
    }

    printf("SQL query prepared (SELECT)\n");

    char nickname[255];
    char password[255];
    bool gender;
    int* listPokemonPlayersize;
    PokemonPlayer* listPokemon[6] = loadPlayerPokemonPlayer(db, nickname, listPokemonPlayersize);
    int maxLvL;
    int story;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
		strcpy(nickname, (char*) sqlite3_column_text(stmt, 1));
        strcpy(password, (char*) sqlite3_column_text(stmt, 2));
        gender = (bool) sqlite3_column_int(stmt, 3);
        maxLvL = sqlite3_column_int(stmt, 4);
        story = sqlite3_column_int(stmt, 5);
    }

    Player* player = (Player*) createPlayer(nickname, password, gender, listPokemon, *listPokemonPlayersize, maxLvL, story);
    printPlayer(player);

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (PokemonPlayer*) NULL;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return (Player*) player;
}

PokemonPlayer** loadPlayerPokemonPlayer(sqlite3* db, char* nickname, int* size) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM Team WHERE idOwner = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    if (sqlite3_bind_text(stmt, 1, nickname, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind nickname: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return NULL;
    }

	printf("SQL query prepared (SELECT)\n");

    PokemonPlayer** pokemonPlayer = malloc(sizeof(*pokemonPlayer) * 6);
    int pokemonlist[6];


	printf("Showing Pokemon:\n");

    int sizeCount = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        pokemonlist[0] = sqlite3_column_int(stmt, 1);
        pokemonlist[1] = sqlite3_column_int(stmt, 2);
        pokemonlist[2] = sqlite3_column_int(stmt, 3);
        pokemonlist[3] = sqlite3_column_int(stmt, 4);
        pokemonlist[4] = sqlite3_column_int(stmt, 5);
        pokemonlist[5] = sqlite3_column_int(stmt, 6);
    }

    for (int i = 0; i < 6; i++)
    {
        if (pokemonlist[i] != NULL)
        {
            pokemonPlayer[sizeCount] = loadPokemonPlayer(db, pokemonlist[i]);
            sizeCount++;
        }
        
    }

    *size = sizeCount;

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return (Pokemon*) NULL;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return (PokemonPlayer**) pokemonPlayer;
}

int insertPlayer(sqlite3* db, Player* player) {
    const char *sql = "INSERT INTO Player (nickname, password, gender, maxLvL, story) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando inserción de Player: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Asignamos parámetros
    sqlite3_bind_text(stmt, 1, player->nickname, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, player->password, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, (int) player->gender);
    sqlite3_bind_int(stmt, 4, player->maxLvL);
    sqlite3_bind_int(stmt, 5, player->story);

    // Ejecutamos
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error insertando Player: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    printf("Player insertado correctamente.\n");

    sqlite3_finalize(stmt);

    return 1;
}