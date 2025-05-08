#include <stdio.h>
#include "moduleMenus.h"
#include "db.h"

int main(void)
{
    printf("Inicio del programa\n");

    sqlite3* db;
    printf("Intentando abrir la base de datos...\n");

    if (sqlite3_open("../DB/pokemon.db", &db) != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    printf("Base de datos abierta correctamente\n");

    Pokemon* pokemon;
    pokemon = (Pokemon*) loadPokemon(db, 6);

    /*Pokemon pokemons[50];
    Jugador jugadores[51];
    Objeto objetos[50];
    Movimiento movimientos[50];

    printf("Cargando datos...\n");

    int num_pokemon = cargar_pokemons(db, pokemons, 50);
    int num_jugadores = cargar_jugadores(db, jugadores, 50);
    int num_objetos = cargar_objetos(db, objetos, 50);
    int num_movs = cargar_movimientos(db, movimientos, 50);

    printf("Pokémon cargados: %d\n", num_pokemon);
    printf("Jugadores cargados: %d\n", num_jugadores);
    printf("Objetos cargados: %d\n", num_objetos);
    printf("Movimientos cargados: %d\n", num_movs);

    insertar_jugador(db, 00012, "Ash", "pikachu123", "M", 1000, 5,  jugadores, 51);

    printf("Finalizando con la inicializacion...\n");
    */
    presentation(db);
    
    sqlite3_close(db);
    return 0;
}
