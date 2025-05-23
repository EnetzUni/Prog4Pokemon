#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sqlite3.h"
#include "db.h"
#include "pokemon.h"
#include "movement.h"
#include "player.h"
#include "type.h"
#include "pc.h"

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
    char nickname[255];
    int* listMovementSize = malloc(sizeof* listMovementSize);
    Movement** listMovement = loadPokemonPlayerMovement(db, id, listMovementSize);
    int xp;
    int curHp;
    Status status;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
		pokemon = loadPokemon(db, sqlite3_column_int(stmt, 0));
        strcpy(nickname, (char*) sqlite3_column_text(stmt, 2));
        xp = sqlite3_column_int(stmt, 3);
        curHp = sqlite3_column_int(stmt, 4);
        status = (Status) (sqlite3_column_int(stmt, 5) - 1);
    }

    pokemonplayer = (PokemonPlayer*) createPokemonPlayer(pokemon, id, nickname, listMovement, *listMovementSize, xp, curHp, status);
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
        printMovement(movement[i]);
        i++;
    }

    *size = i;

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return NULL;
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

    Movement* movement;
    char name[255];
    Type type;
    Category category;
    Status status;
    int statusaccuracy;
    int power;
    int accuracy;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
		strcpy(name, (char *) sqlite3_column_text(stmt, 1));
        type = (Type) (sqlite3_column_int(stmt, 2) - 1);
        category = (Category) (sqlite3_column_int(stmt, 3) - 1);
        power = sqlite3_column_int(stmt, 4);
        accuracy = sqlite3_column_int(stmt, 5);
	}

    movement = (Movement*) createMovement(id, name, type, category, (Status) NULL, (int) NULL, power, accuracy);

    if (movement->power != 0)
    {
        printf("Showing Movement:\n");
        printMovement(movement);
    }

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return NULL;
	}

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

    char password[255];
    bool gender;
    int* listPokemonPlayersize = malloc(sizeof* listPokemonPlayersize);
    PokemonPlayer** listPokemon = loadPlayerPokemonPlayer(db, nickname, listPokemonPlayersize);
    int maxLvL;
    int story;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(password, (char*) sqlite3_column_text(stmt, 1));
        gender = (bool) sqlite3_column_int(stmt, 2);
        maxLvL = sqlite3_column_int(stmt, 3);
        story = sqlite3_column_int(stmt, 4);
    }

    Player* player = (Player*) createPlayer(nickname, password, gender, listPokemon, *listPokemonPlayersize, maxLvL, story);
    printPlayer(player);

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return NULL;
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
        if (&pokemonlist[i] != NULL)
        {
            pokemonPlayer[sizeCount] = loadPokemonPlayer(db, pokemonlist[i]);
            sizeCount++;
        }
        
    }

    *size = sizeCount;

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return NULL;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return (PokemonPlayer**) pokemonPlayer;
}

int deletePlayerTeam(sqlite3* db, Player* player) {
    const char *sql = "DELETE FROM Team WHERE idOwner = ?";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando DELETE: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Asignamos parámetros
    sqlite3_bind_text(stmt, 0, player->nickname, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error ejecutando DELETE: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("PlayerTeam eliminado correctamente.\n");
    return 1;
}

int insertPlayerTeam(sqlite3* db, Player* player) {
    deletePlayerTeam(db, player);

    const char *sql = "INSERT INTO Team (idOwner, pokemon1, pokemon2, pokemon3, pokemon4, pokemon5, pokemon6) VALUES (?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando inserción de Player: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Asignamos parámetros
    sqlite3_bind_text(stmt, 0, player->nickname, -1, SQLITE_TRANSIENT);

    for (int i = 0; i < player->listPokemonSize; i++)
    {
        sqlite3_bind_int(stmt, i + 1, player->listPokemon[i]->pokeid);
    }

    // Ejecutamos
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error insertando Player: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    printf("PlayerTeam insertado correctamente.\n");

    sqlite3_finalize(stmt);

    return 1;
}

int insertPlayer(sqlite3* db, Player* player) {
    const char *sql = "INSERT OR IGNORE INTO Player (nickname, password, gender, maxLvL, story) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando inserción de Player: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Asignamos parámetros
    sqlite3_bind_text(stmt, 0, player->nickname, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 1, player->password, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, (int) player->gender);
    sqlite3_bind_int(stmt, 3, player->maxLvL);
    sqlite3_bind_int(stmt, 4, player->story);

    // Ejecutamos
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error insertando Player: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    insertPlayerTeam(db, player);

    printf("Player insertado correctamente.\n");

    sqlite3_finalize(stmt);

    return 1;
}

PC* loadPc(sqlite3* db, char* nickname) {
    int* size = loadPcCount(db, nickname);

    sqlite3_stmt* stmt;
    const char* sql = "SELECT * FROM Pc WHERE idPlayer = ?";

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

    PokemonPlayer** pokemonPlayer = malloc(sizeof(*pokemonPlayer) * *size);

	printf("Showing Pokemon:\n");

    int i = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        pokemonPlayer[i] = loadPokemonPlayer(db, sqlite3_column_int(stmt, 1));
        i++;
    }

    PC* pc = createPc(nickname, pokemonPlayer, *size);

	printf("Prepared statement finalized (SELECT)\n");

	return (PC*) pc;
}

int* loadPcCount(sqlite3* db, char* nickname) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT COUNT(*) FROM Pc WHERE idPlayer = ?";

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

    int* size = malloc(sizeof* size);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *size = sqlite3_column_int(stmt, 0);
    }

    return size;
}

int insertPokemonPlayer(sqlite3* db, PokemonPlayer* pokemon) {
    const char *sql = "INSERT OR IGNORE INTO PokemonPlayer (idPokemon, pokeid, nickname, xp, curHp, status, move1, move2, mov3, move4) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando inserción de Player: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Asignamos parámetros
    sqlite3_bind_int(stmt, 0, pokemon->pokemon->id);
    sqlite3_bind_int(stmt, 1, pokemon->pokeid);
    sqlite3_bind_text(stmt, 2, pokemon->nickname, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, pokemon->xp);
    sqlite3_bind_int(stmt, 4, pokemon->curHp);
    sqlite3_bind_int(stmt, 5, (int) pokemon->status + 1);

    int sqlcount = 0;
    for (int i = 0; i < pokemon->listMovementSize; i++)
    {
        sqlite3_bind_int(stmt, 6 + sqlcount, pokemon->listMovement[i]->id);
        sqlcount++;
    }

    // Ejecutamos
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error insertando Player: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    printf("PokemonPlayer insertado correctamente.\n");

    sqlite3_finalize(stmt);

    return 1;
}

int deletePc(sqlite3* db, PC* pc) {
    const char *sql = "DELETE FROM Pc WHERE idPlayer = ?";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando DELETE: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Asignamos parámetros
    sqlite3_bind_text(stmt, 0, pc->nickname, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error ejecutando DELETE: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("PlayerTeam eliminado correctamente.\n");
    return 1;
}

int insertPc(sqlite3* db, PC* pc) {
    deletePc(db, pc);

    const char *sql = "INSERT INTO Pc (idPlayer, idPokemonPlayer) VALUES (?, ?)";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando inserción: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Begin transaction (optional but recommended for speed)
    sqlite3_exec(db, "BEGIN TRANSACTION;", NULL, NULL, NULL);

    for (int i = 0; i < pc->pcListSize; i++) {

        sqlite3_bind_text(stmt, 0, pc->nickname, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 1, pc->pcList[i]->pokeid);
        insertPokemonPlayer(db, pc->pcList[i]);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            printf("Error insertando PC #%d: %s\n", i, sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            return 0;
        }

        sqlite3_reset(stmt); // Reset the statement for reuse
        sqlite3_clear_bindings(stmt); // Optional: clear previous bindings
    }

    // Commit transaction
    sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);

    sqlite3_finalize(stmt);
    printf("PC insertados correctamente.\n");
    return 1;
}

void initializeDb(sqlite3* db) {
    Pokemon* pokemon1 = loadPokemon(db, 34);
    Pokemon* pokemon2 = loadPokemon(db, 392);
    Pokemon* pokemon3 = loadPokemon(db, 282);
    Pokemon* pokemon4 = loadPokemon(db, 487);
    Pokemon* pokemon5 = loadPokemon(db, 493);

    Movement** movementpokemonplayer1 = createRandomMovementList(db);
    PokemonPlayer* pokemonplayer1 = createPokemonPlayer(pokemon1, -1, NULL, movementpokemonplayer1, 4, 125000, calculateBattleHp(pokemon1->hp, calculateLvl(125000)), (Type) NULL);
    Movement** movementpokemonplayer2 = createRandomMovementList(db);
    PokemonPlayer* pokemonplayer2 = createPokemonPlayer(pokemon1, -1, NULL, movementpokemonplayer2, 4, 125000, calculateBattleHp(pokemon1->hp, calculateLvl(125000)), (Type) NULL);
    Movement** movementpokemonplayer3 = createRandomMovementList(db);
    PokemonPlayer* pokemonplayer3 = createPokemonPlayer(pokemon1, -1, NULL, movementpokemonplayer3, 4, 125000, calculateBattleHp(pokemon1->hp, calculateLvl(125000)), (Type) NULL);
    Movement** movementpokemonplayer4 = createRandomMovementList(db);
    PokemonPlayer* pokemonplayer4 = createPokemonPlayer(pokemon1, -1, NULL, movementpokemonplayer4, 4, 125000, calculateBattleHp(pokemon1->hp, calculateLvl(125000)), (Type) NULL);
    Movement** movementpokemonplayer5 = createRandomMovementList(db);
    PokemonPlayer* pokemonplayer5 = createPokemonPlayer(pokemon1, -1, NULL, movementpokemonplayer5, 4, 125000, calculateBattleHp(pokemon1->hp, calculateLvl(125000)), (Type) NULL);

    Player* player = createPlayer("admin", "1234", (bool) 0, NULL, 0, 50, 0);
    insertPlayer(db, player);
    player = loadPlayer(db, "admin");
    addPlayerPokemonPlayer(db, player, pokemonplayer1);
    addPlayerPokemonPlayer(db, player, pokemonplayer2);
    insertPlayer(db, player);

    PC* pc = createPc("admin", NULL, 0);
    insertPc(db, pc);
    pc = loadPc(db, "admin");
    addPcPokemonPlayer(db, pc, pokemonplayer3);
    addPcPokemonPlayer(db, pc, pokemonplayer4);
    addPcPokemonPlayer(db, pc, pokemonplayer5);
    insertPc(db, pc);
}