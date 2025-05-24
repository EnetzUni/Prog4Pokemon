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
    const char* sql = "SELECT idPokemon, pokeid, nickname, xp, curHp, move1, move2, move3, move4 FROM PokemonPlayer WHERE pokeid = ?";

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
    int movementlist[4];
    Movement** listMovement = malloc(sizeof(*listMovement) * 4);
    int xp;
    int curHp;
    Status status;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
		pokemon = loadPokemon(db, sqlite3_column_int(stmt, 0));
        strcpy(nickname, (char*) sqlite3_column_text(stmt, 2));
        xp = sqlite3_column_int(stmt, 3);
        curHp = sqlite3_column_int(stmt, 4);
        status = (Status) (sqlite3_column_int(stmt, 5) - 1);
        movementlist[0] = sqlite3_column_int(stmt, 6);
        movementlist[1] = sqlite3_column_int(stmt, 7);
        movementlist[2] = sqlite3_column_int(stmt, 8);
        movementlist[3] = sqlite3_column_int(stmt, 9);
    }

    int sizeCount = 0;
    for (int i = 0; i < 4; i++)
    {
        if (&movementlist[i] != NULL)
        {
            listMovement[sizeCount] = loadMovement(db, movementlist[i]);
            sizeCount++;
        }
        
    }

    pokemonplayer = (PokemonPlayer*) createPokemonPlayer(pokemon, id, nickname, listMovement, sizeCount, xp, curHp, status);
    printPokemonPlayer(pokemonplayer);

	if (sqlite3_finalize(stmt) != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return NULL;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return (PokemonPlayer*) pokemonplayer;
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

    movement = (Movement*) createMovement(id, name, type, category, (Status) -1, (int) NULL, power, accuracy);

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
    const char* sql = "SELECT * FROM Player WHERE nickname = ?";

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
    if (!pokemonPlayer) {
        fprintf(stderr, "Failed to allocate memory for pokemonPlayer\n");
        sqlite3_finalize(stmt);
        return NULL;
    }

    int pokemonlist[6] = {0};  // Initialize to 0

    int sizeCount = 0;
    int stepResult = sqlite3_step(stmt);

    if (stepResult == SQLITE_ROW) {
        // Assuming columns 1..6 hold the Pokemon IDs
        for (int i = 0; i < 6; i++) {
            pokemonlist[i] = sqlite3_column_int(stmt, i + 1);
        }
    } else if (stepResult == SQLITE_DONE) {
        // No rows found
        printf("No team found for owner %s\n", nickname);
        sqlite3_finalize(stmt);
        free(pokemonPlayer);
        *size = 0;
        return NULL;
    } else {
        fprintf(stderr, "Error stepping through statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        free(pokemonPlayer);
        return NULL;
    }

    // Load PokemonPlayer pointers for non-zero IDs
    for (int i = 0; i < 6; i++) {
        if (pokemonlist[i] != 0) {
            PokemonPlayer* p = loadPokemonPlayer(db, pokemonlist[i]);
            if (p != NULL) {
                pokemonPlayer[sizeCount++] = p;
            } else {
                // Handle failure of loadPokemonPlayer if needed
                fprintf(stderr, "Failed to load Pokemon with ID %d\n", pokemonlist[i]);
            }
        }
    }

    *size = sizeCount;

    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        fprintf(stderr, "Error finalizing statement: %s\n", sqlite3_errmsg(db));
        // We still return the loaded data
    }

    return pokemonPlayer;
}

int deletePlayerTeam(sqlite3* db, Player* player) {
    const char *sql = "DELETE FROM Team WHERE idOwner = ?";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando DELETE: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Bind parameter with index 1, NOT 0
    sqlite3_bind_text(stmt, 1, player->nickname, -1, SQLITE_TRANSIENT);

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
        printf("Error preparando inserción de PlayerTeam: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Bind owner nickname
    if (player->nickname == NULL) {
        printf("Error: nickname del jugador es NULL.\n");
        sqlite3_finalize(stmt);
        return 0;
    }
    sqlite3_bind_text(stmt, 1, player->nickname, -1, SQLITE_TRANSIENT);

    // Bind 6 Pokémon or NULL
    for (int i = 0; i < 6; i++) {
        if (i < player->listPokemonSize && player->listPokemon[i] != NULL) {
            sqlite3_bind_int(stmt, i + 2, player->listPokemon[i]->pokeid);
        } else {
            sqlite3_bind_null(stmt, i + 2);
        }
    }

    // Execute
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error insertando PlayerTeam: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    printf("PlayerTeam insertado correctamente.\n");
    sqlite3_finalize(stmt);
    return 1;
}

int insertPlayer(sqlite3* db, Player* player) {
    const char *sql = "INSERT INTO Player (nickname, password, gender, maxLvL, story) VALUES (?, ?, ?, ?, ?) ON CONFLICT(nickname) DO UPDATE SET password = excluded.password, gender = excluded.gender, maxLvL = excluded.maxLvL, story = excluded.story;";
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
    const char *sql = "INSERT INTO PokemonPlayer (idPokemon, pokeid, nickname, xp, curHp, status, move1, move2, move3, move4) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?) ON CONFLICT(pokeid) DO UPDATE SET idPokemon = excluded.idPokemon, nickname = excluded.nickname, xp = excluded.xp, curHp = excluded.curHp, status = excluded.status, move1 = excluded.move1, move2 = excluded.move2, move3 = excluded.move3, move4 = excluded.move4;";
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error preparando inserción de Player: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Corrected indices
    sqlite3_bind_int(stmt, 1, pokemon->pokemon->id);
    sqlite3_bind_int(stmt, 2, pokemon->pokeid);
    sqlite3_bind_text(stmt, 3, pokemon->nickname, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, pokemon->xp);
    sqlite3_bind_int(stmt, 5, pokemon->curHp);
    sqlite3_bind_int(stmt, 6, (int)pokemon->status + 1);

    // Bind moves or NULLs
    for (int i = 0; i < 4; i++) {
        if (i < pokemon->listMovementSize && pokemon->listMovement[i] != NULL) {
            sqlite3_bind_int(stmt, 7 + i, pokemon->listMovement[i]->id);
        } else {
            sqlite3_bind_null(stmt, 7 + i);
        }
    }

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

    // Bind parameter index 1
    sqlite3_bind_text(stmt, 1, pc->nickname, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error ejecutando DELETE: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    printf("PC eliminado correctamente.\n");
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

        sqlite3_bind_text(stmt, 1, pc->nickname, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, pc->pcList[i]->pokeid);
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
    PokemonPlayer* pokemonplayer1 = createPokemonPlayer(pokemon1, 1000, pokemon1->name, movementpokemonplayer1, 4, 125000, calculateBattleHp(pokemon1->hp, calculateLvl(125000)), (Type) -1);
    printPokemonPlayer(pokemonplayer1);
    insertPokemonPlayer(db, pokemonplayer1);
    Movement** movementpokemonplayer2 = createRandomMovementList(db);
    PokemonPlayer* pokemonplayer2 = createPokemonPlayer(pokemon2, 1001, pokemon2->name, movementpokemonplayer2, 4, 125000, calculateBattleHp(pokemon2->hp, calculateLvl(125000)), (Type) -1);
    printPokemonPlayer(pokemonplayer2);
    insertPokemonPlayer(db, pokemonplayer2);
    Movement** movementpokemonplayer3 = createRandomMovementList(db);
    PokemonPlayer* pokemonplayer3 = createPokemonPlayer(pokemon3, 1002, pokemon3->name, movementpokemonplayer3, 4, 125000, calculateBattleHp(pokemon3->hp, calculateLvl(125000)), (Type) -1);
    printPokemonPlayer(pokemonplayer3);
    insertPokemonPlayer(db, pokemonplayer3);
    Movement** movementpokemonplayer4 = createRandomMovementList(db);
    PokemonPlayer* pokemonplayer4 = createPokemonPlayer(pokemon4, 1003, pokemon4->name, movementpokemonplayer4, 4, 125000, calculateBattleHp(pokemon4->hp, calculateLvl(125000)), (Type) -1);
    printPokemonPlayer(pokemonplayer4);
    insertPokemonPlayer(db, pokemonplayer4);
    Movement** movementpokemonplayer5 = createRandomMovementList(db);
    PokemonPlayer* pokemonplayer5 = createPokemonPlayer(pokemon5, 1004, pokemon5->name, movementpokemonplayer5, 4, 125000, calculateBattleHp(pokemon5->hp, calculateLvl(125000)), (Type) -1);
    printPokemonPlayer(pokemonplayer5);
    insertPokemonPlayer(db, pokemonplayer5);

    Player* player = createPlayer("admin", "1234", (bool) 1, NULL, 0, 50, 0);
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