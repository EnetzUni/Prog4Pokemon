#include "ficheros.h"
#include "baseDeDatos.h"
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Jugador obtenerJugadorPorNombre(char* nombreJugador){

    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    Jugador jugador;
    
    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) == SQLITE_OK) {

        //Sentencia sql
        char sql[] = "select * from Jugador where name = ?";

        //Preparar sentencia
        sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        sqlite3_bind_text(stmt, 1, nombreJugador, strlen(nombreJugador), SQLITE_STATIC);

        //Recuperar el resultados

        result = sqlite3_step(stmt);
        
        if (result == SQLITE_ROW) {
            
            char* nombre = (char*)sqlite3_column_text(stmt, 1);
            jugador.nombre = malloc(strlen(nombre) + 1);
            strcpy(jugador.nombre, nombre);

            char* contrasena = (char*)sqlite3_column_text(stmt, 2);
            jugador.contrasena = malloc(strlen(contrasena) + 1);
            strcpy(jugador.contrasena, contrasena);

            jugador.genero = sqlite3_column_int(stmt,3);

            jugador.dinero = sqlite3_column_int(stmt,4);

            jugador.nivelMaximo = sqlite3_column_int(stmt,5);

            jugador.historia = sqlite3_column_int(stmt,6);

            jugador.cant_p = 0;
            printf("Id del jugador%i\n",sqlite3_column_int(stmt,0));
            jugador.pokemons = obtenerPokemonJugador(sqlite3_column_int(stmt,0), &jugador.cant_p);
            
        }

        //Cerrar select
        sqlite3_finalize(stmt);
        
        //Cerrar base de datos
        sqlite3_close(db);
    }
    return jugador;
}

char* obtenerEfectoPorId(int id){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    char* efecto;

    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        return NULL;
    }

    //Sentencia sql
    char sql[] = "select * from Efecto where id = ?";

    //Preparar sentencia
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

	//Recuperar el resultados

	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {

        char* nombre = (char*)sqlite3_column_text(stmt, 1);
        efecto = malloc(strlen(nombre) + 1);
        strcpy(efecto, nombre);

		
	}

    //Cerrar select
	sqlite3_finalize(stmt);
    
    //Cerrar base de datos
    sqlite3_close(db);

    return efecto;
}

char* obtenerStatPorId(int id){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    char* stat;

    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        return NULL;
    }

    //Sentencia sql
    char sql[] = "select * from Stat where id = ?";

    //Preparar sentencia
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

	//Recuperar el resultados

	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {

        char* nombre = (char*)sqlite3_column_text(stmt, 1);
        stat = malloc(strlen(nombre) + 1);
        strcpy(stat, nombre);

		
	}

    //Cerrar select
	sqlite3_finalize(stmt);
    
    //Cerrar base de datos
    sqlite3_close(db);

    return stat;
}

char* obtenerTipoPorId(int id){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    char* tipo;

    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        return NULL;
    }

    //Sentencia sql
    char sql[] = "select * from Tipo where id = ?";

    //Preparar sentencia
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

	//Recuperar el resultados

	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {

        char* nombre = (char*)sqlite3_column_text(stmt, 1);
        tipo = malloc(strlen(nombre) + 1);
        strcpy(tipo, nombre);

		
	}

    //Cerrar select
	sqlite3_finalize(stmt);
    
    //Cerrar base de datos
    sqlite3_close(db);

    return tipo;
}

Pokemon* obtenerPokemons(int* cant_p){

    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    Pokemon* pokemons = NULL;
    *cant_p = 0;

    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        return NULL;
    }

    //Sentencia sql
    char sql[] = "select * from Pokemon";

    //Preparar sentencia
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);

	//Recorrer los resultados
	do {
		result = sqlite3_step(stmt) ;

		if (result == SQLITE_ROW) {
            
            //Ampliar en una el array de pokemons
            Pokemon* aux = (Pokemon*) malloc(sizeof(Pokemon)*((*cant_p)+1));
            for(int i=0; i<*cant_p;i++){
                aux[i]= pokemons[i];
            }
            free(pokemons);
            pokemons=aux;

            //Recuperar y añadir pokemon

			char* nombre = (char*)sqlite3_column_text(stmt, 1);
            pokemons[*cant_p].nombre = malloc(strlen(nombre) + 1);
            strcpy(pokemons[*cant_p].nombre, nombre);

            //Recuperar tipo/s
            int tipo_id_1 = sqlite3_column_int(stmt, 2);
            pokemons[*cant_p].tipos = malloc(sizeof(char*));
            pokemons[*cant_p].tipos[0] = obtenerTipoPorId(tipo_id_1);
            pokemons[*cant_p].cant_tipo = 1;

            int tipo_id_2 = sqlite3_column_int(stmt, 3);
            if (tipo_id_2 != 0)
            {   
                char** aux = malloc(sizeof(char*)*2);
                aux[0] = pokemons[*cant_p].tipos[0];
                free(pokemons[*cant_p].tipos);
                pokemons[*cant_p].tipos = aux; 
                pokemons[*cant_p].tipos[1] = obtenerTipoPorId(tipo_id_2);
                pokemons[*cant_p].cant_tipo = 2;
            }

            pokemons[*cant_p].ps = sqlite3_column_int(stmt, 4);

            pokemons[*cant_p].ps = sqlite3_column_int(stmt, 4);

            pokemons[*cant_p].ataque = sqlite3_column_int(stmt, 5);

            pokemons[*cant_p].defensa = sqlite3_column_int(stmt, 6);

            pokemons[*cant_p].ataqueEspecial = sqlite3_column_int(stmt, 7);

            pokemons[*cant_p].defensaEspecial = sqlite3_column_int(stmt, 8);
           
            pokemons[*cant_p].velocidad = sqlite3_column_int(stmt, 9);

            //Aumentar el contador de pokemons
            (*cant_p)++;
		}
	} while (result == SQLITE_ROW);

    
    //Cerrar select
	sqlite3_finalize(stmt);
    
    //Cerrar base de datos
    sqlite3_close(db);

    return pokemons;
}

Pokemon obtenerPokemonsPorId(int id){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    Pokemon pokemon;

    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) == SQLITE_OK) {
        
    

        //Sentencia sql
        char sql[] = "select * from Pokemon where id = ?";

        //Preparar sentencia
        sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);

        //Recorrer los resultados
        result = sqlite3_step(stmt) ;

        if (result == SQLITE_ROW) {
                
            //Recuperar pokemon

            char* nombre = (char*)sqlite3_column_text(stmt, 1);
            pokemon.nombre = malloc(strlen(nombre) + 1);
            strcpy(pokemon.nombre, nombre);

            //Recuperar tipo/s
            int tipo_id_1 = sqlite3_column_int(stmt, 2);
            pokemon.tipos = malloc(sizeof(char*));
            pokemon.tipos[0] = obtenerTipoPorId(tipo_id_1);
            pokemon.cant_tipo = 1;

            int tipo_id_2 = sqlite3_column_int(stmt, 3);
            if (tipo_id_2 != 0)
            {   
                char** aux = malloc(sizeof(char*)*2);
                aux[0] = pokemon.tipos[0];
                free(pokemon.tipos);
                pokemon.tipos = aux; 
                pokemon.tipos[1] = obtenerTipoPorId(tipo_id_2);
                pokemon.cant_tipo = 2;
            }

            pokemon.ps = sqlite3_column_int(stmt, 4);

            pokemon.ataque = sqlite3_column_int(stmt, 5);

            pokemon.defensa = sqlite3_column_int(stmt, 6);

            pokemon.ataqueEspecial = sqlite3_column_int(stmt, 7);

            pokemon.defensaEspecial = sqlite3_column_int(stmt, 8);
            
            pokemon.velocidad = sqlite3_column_int(stmt, 9);

        }

        //Cerrar select
	    sqlite3_finalize(stmt);
    
        //Cerrar base de datos
        sqlite3_close(db);

    }
    
    return pokemon;
}

Pokemon* obtenerPokemonJugador(int id_jugador, int *cant_p){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    Pokemon* pokemons;

    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) == SQLITE_OK) {
        
        //Sentencia sql
        char sql[] = "select * from PokemonJugador where idJugador = ?";

        //Preparar sentencia
        sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id_jugador);

        //Recorrer los resultados
        do{
            result = sqlite3_step(stmt) ;

            if (result == SQLITE_ROW) {
                
                //Ampliar en una el array de pokemons
                Pokemon* aux = (Pokemon*) malloc(sizeof(Pokemon)*((*cant_p)+1));
                for(int i=0; i<*cant_p;i++){
                    aux[i]= pokemons[i];
                }
                free(pokemons);
                pokemons=aux;

                //Recuperar datos pokemon comunes

                Pokemon pokemon = obtenerPokemonsPorId(sqlite3_column_int(stmt, 2));

                pokemons[*cant_p].tipos = pokemon.tipos;

                pokemons[*cant_p].ps = pokemon.ps;

                pokemons[*cant_p].ataque = pokemon.ataque;

                pokemons[*cant_p].defensa = pokemon.defensa;

                pokemons[*cant_p].ataqueEspecial = pokemon.ataqueEspecial;

                pokemons[*cant_p].defensaEspecial = pokemon.defensaEspecial;
                
                pokemons[*cant_p].velocidad = pokemon.velocidad;

                //Datos propias del pokemon del jugador
                char* nombre = (char*)sqlite3_column_text(stmt, 3);
                pokemons[*cant_p].nombre = malloc(strlen(nombre) + 1);
                strcpy(pokemons[*cant_p].nombre, nombre);

                pokemons[*cant_p].vidaActual = sqlite3_column_int(stmt, 4);

                pokemons[*cant_p].nivel = sqlite3_column_int(stmt, 5);

                pokemons[*cant_p].experiencia = sqlite3_column_int(stmt, 6);

                pokemons[*cant_p].activo = sqlite3_column_int(stmt, 11);

                //Recuperar movimientos
                pokemons[*cant_p].movimientos = malloc(sizeof(Movimiento)*4);

                pokemons[*cant_p].movimientos[0] = obtenerMovimientoPorId(sqlite3_column_int(stmt, 7));

                pokemons[*cant_p].movimientos[1] = obtenerMovimientoPorId(sqlite3_column_int(stmt, 8));

                pokemons[*cant_p].movimientos[2] = obtenerMovimientoPorId(sqlite3_column_int(stmt, 9));

                pokemons[*cant_p].movimientos[3] = obtenerMovimientoPorId(sqlite3_column_int(stmt, 10));

               (*cant_p)++;
           
            }
        }while(result == SQLITE_ROW);
        //Cerrar select
	    sqlite3_finalize(stmt);
    
        //Cerrar base de datos
        sqlite3_close(db);

    }
    
    return pokemons;
}

Movimiento obtenerMovimientoPorId(int id){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    Movimiento movimiento;

    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) == SQLITE_OK) {

        //Sentencia sql
        char sql[] = "select * from Movimiento where id = ?";

        //Preparar sentencia
        sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
        sqlite3_bind_int(stmt, 1, id);

        //Recorrer los resultados
        result = sqlite3_step(stmt) ;

        if (result == SQLITE_ROW) {
                
            //Recuperar datos movimientos

            char* nombre = (char*)sqlite3_column_text(stmt, 3);
            movimiento.nombre = malloc(strlen(nombre) + 1);
            strcpy(movimiento.nombre, nombre);

            int tipo_id = sqlite3_column_int(stmt, 1);
            movimiento.tipo = obtenerTipoPorId(tipo_id);

            int tipo_categoria = sqlite3_column_int(stmt, 2);
            movimiento.categoria = obtenerCategoriaMovimientoPorId(tipo_categoria);

            //int tipo_efecto = sqlite3_column_int(stmt, 3);
            //movimiento.efecto = obtenerEfectoPorId(tipo_efecto);

            movimiento.potencia = sqlite3_column_int(stmt, 4);

            movimiento.precision = sqlite3_column_int(stmt, 5);

            movimiento.prioridad = sqlite3_column_int(stmt, 6);

            /*
            //Recuperar stats
            int* idStats = obtenerIdStatPorIdMovimiento(sqlite3_column_int(stmt, 0), &(movimiento.cant_stats));
            movimiento.stats = malloc(sizeof(char*)*movimiento.cant_stats);
            for(int i=0; i<movimiento.cant_stats;i++){
                movimiento.stats[i] = obtenerStatPorId(idStats[i]);
            }
            */
        }

        //Cerrar select
	    sqlite3_finalize(stmt);
    
        //Cerrar base de datos
        sqlite3_close(db);

    }
    
    return movimiento;
}

Movimiento* obtenerMovimientos(int *cant_m){

    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    Movimiento* movimientos;
    *cant_m = 0;

    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) == SQLITE_OK) {
        
        //Sentencia sql
        char sql[] = "select * from Movimiento";

        //Preparar sentencia
        sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);

        //Recorrer los resultados
        do{
            result = sqlite3_step(stmt) ;

            if (result == SQLITE_ROW) {
                
                //Ampliar en una el array de pokemons
                Movimiento* aux = (Movimiento*) malloc(sizeof(Movimiento)*((*cant_m)+1));
                for(int i=0; i<*cant_m;i++){
                    aux[i]= movimientos[i];
                }
                free(movimientos);
                movimientos=aux;

                //Recuperar datos movimientos

                char* nombre = (char*)sqlite3_column_text(stmt, 3);
                movimientos[*cant_m].nombre = malloc(strlen(nombre) + 1);
                strcpy(movimientos[*cant_m].nombre, nombre);

                int tipo_id = sqlite3_column_int(stmt, 1);
                movimientos[*cant_m].tipo = obtenerTipoPorId(tipo_id);

                int tipo_categoria = sqlite3_column_int(stmt, 2);
                movimientos[*cant_m].categoria = obtenerCategoriaMovimientoPorId(tipo_categoria);

                //int tipo_efecto = sqlite3_column_int(stmt, 3);
                //movimientos[*cant_m].efecto = obtenerEfectoPorId(tipo_efecto);

                movimientos[*cant_m].potencia = sqlite3_column_int(stmt, 4);

                movimientos[*cant_m].precision = sqlite3_column_int(stmt, 5);

                movimientos[*cant_m].prioridad = sqlite3_column_int(stmt, 6);

                /*
                //Recuperar stats
                int* idStats = obtenerIdStatPorIdMovimiento(sqlite3_column_int(stmt, 0), &(movimientos[*cant_m].cant_stats));
                movimientos[*cant_m].stats = malloc(sizeof(char*)*movimientos[*cant_m].cant_stats);
                for(int i=0; i<movimientos[*cant_m].cant_stats;i++){
                    movimientos[*cant_m].stats[i] = obtenerStatPorId(idStats[i]);
                }
                */
                (*cant_m)++;

            }
        }while(result == SQLITE_ROW);
        
        //Cerrar select
	    sqlite3_finalize(stmt);
    
        //Cerrar base de datos
        sqlite3_close(db);

    }
    
    return movimientos;

}

int* obtenerIdStatPorIdMovimiento(int idMovimiento, int* cant_stat){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    int* idStats = NULL;
    *cant_stat = 0;

    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        return NULL;
    }

    //Sentencia sql
    char sql[] = "select * from StatMovimiento where idMovimiento = ?";

    //Preparar sentencia
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    sqlite3_bind_int(stmt, 1, idMovimiento);

	//Recorrer los resultados
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
            
            //Ampliar en una el array de ides de stats
            int* aux = malloc(sizeof(int)*((*cant_stat)+1));
            for(int i=0; i<*cant_stat;i++){
                aux[i]= idStats[i];
            }
            free(idStats);
            idStats=aux;

            //Recuperar y añadir idStat
            idStats[*cant_stat] = sqlite3_column_int(stmt, 1);

            //Aumentar el contador de pokemons
            (*cant_stat)++;
		}
	} while (result == SQLITE_ROW);

    
    //Cerrar select
	sqlite3_finalize(stmt);
    
    //Cerrar base de datos
    sqlite3_close(db);

    return idStats;
}

char* obtenerCategoriaMovimientoPorId(int id){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int result;
    char* categoriaMovimiento;

    //Abrrir base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        return NULL;
    }

    //Sentencia sql
    char sql[] = "select * from CategoriaMovimiento where id = ?";

    //Preparar sentencia
	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

	//Recuperar el resultados

	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {

        char* nombre = (char*)sqlite3_column_text(stmt, 1);
        categoriaMovimiento = malloc(strlen(nombre) + 1);
        strcpy(categoriaMovimiento, nombre);

		
	}

    //Cerrar select
	sqlite3_finalize(stmt);
    
    //Cerrar base de datos
    sqlite3_close(db);

    return categoriaMovimiento;
}

// Función para insertar un jugador en la base de datos
void insertar_jugador(Jugador jugador) {
    char *sql = "INSERT INTO Jugador (nombre, contrasena, genero, dinero, nivelMaximo, historia) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3 *db;
    sqlite3_stmt *stmt;

    // Abrir la base de datos
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        printf("Error abriendo la base de datos");
        return;
    }

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    // Bind de los valores
    sqlite3_bind_text(stmt, 1, jugador.nombre, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, jugador.contrasena, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, jugador.genero);
    sqlite3_bind_int(stmt, 4, jugador.dinero);
    sqlite3_bind_int(stmt, 5, jugador.nivelMaximo);
    sqlite3_bind_int(stmt, 6, jugador.historia);

    // Ejecutar la consulta
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error ejecutando la consulta: %s\n", sqlite3_errmsg(db));
    }

    // Liberar memoria
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
    

// Función para modificar un jugador en la base de datos
void modificar_jugador(Jugador jugador) {
    char *sql = "UPDATE Jugador SET contrasena = ?, genero = ?, dinero = ?, nivelMaximo = ?, historia = ? WHERE nombre = ?;";
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        printf("Error abriendo la base de datos");
        return;
    }
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    sqlite3_bind_text(stmt, 1, jugador.contrasena, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, jugador.genero);
    sqlite3_bind_int(stmt, 3, jugador.dinero);
    sqlite3_bind_int(stmt, 4, jugador.nivelMaximo);
    sqlite3_bind_int(stmt, 5, jugador.historia);
    sqlite3_bind_text(stmt, 6, jugador.nombre, -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error ejecutando la consulta: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    }
    
// Función para insertar un Pokémon en la base de datos
void insertar_pokemon(Pokemon pokemon) {
    char *sql = "INSERT INTO Pokemon (nombre, vidaActual, ps, ataque, defensa, ataqueEspecial, defensaEspecial, velocidad, nivel, experiencia, activo) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3 *db;
    sqlite3_stmt *stmt;   
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        printf("Error abriendo la base de datos");
        return;
    }
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    sqlite3_bind_text(stmt, 1, pokemon.nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, pokemon.vidaActual);
    sqlite3_bind_int(stmt, 3, pokemon.ps);
    sqlite3_bind_int(stmt, 4, pokemon.ataque);
    sqlite3_bind_int(stmt, 5, pokemon.defensa);
    sqlite3_bind_int(stmt, 6, pokemon.ataqueEspecial);
    sqlite3_bind_int(stmt, 7, pokemon.defensaEspecial);
    sqlite3_bind_int(stmt, 8, pokemon.velocidad);
    sqlite3_bind_int(stmt, 9, pokemon.nivel);
    sqlite3_bind_int(stmt, 10, pokemon.experiencia);
    sqlite3_bind_int(stmt, 11, pokemon.activo);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error ejecutando la consulta: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    }
    

// Función para modificar un Pokémon en la base de datos
void modificar_pokemon(Pokemon pokemon) {
    char *sql = "UPDATE Pokemon SET vidaActual = ?, ps = ?, ataque = ?, defensa = ?, ataqueEspecial = ?, defensaEspecial = ?, velocidad = ?, nivel = ?, experiencia = ?, activo = ? WHERE nombre = ?;";
    sqlite3 *db;
    sqlite3_stmt *stmt;
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        printf("Error abriendo la base de datos");
        return;
    }
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    sqlite3_bind_int(stmt, 1, pokemon.vidaActual);
    sqlite3_bind_int(stmt, 2, pokemon.ps);
    sqlite3_bind_int(stmt, 3, pokemon.ataque);
    sqlite3_bind_int(stmt, 4, pokemon.defensa);
    sqlite3_bind_int(stmt, 5, pokemon.ataqueEspecial);
    sqlite3_bind_int(stmt, 6, pokemon.defensaEspecial);
    sqlite3_bind_int(stmt, 7, pokemon.velocidad);
    sqlite3_bind_int(stmt, 8, pokemon.nivel);
    sqlite3_bind_int(stmt, 9, pokemon.experiencia);
    sqlite3_bind_int(stmt, 10, pokemon.activo);
    sqlite3_bind_text(stmt, 11, pokemon.nombre, -1, SQLITE_STATIC);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error ejecutando la consulta: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    }

// Función para insertar un movimiento en la base de datos
void insertar_movimiento(Movimiento movimiento) {
    char *sql = "INSERT INTO Movimiento (nombre, tipo, potencia, categoria, efecto, precision, prioridad) VALUES (?, ?, ?, ?, ?, ?, ?);";
    sqlite3 *db;
    sqlite3_stmt *stmt;

    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        printf("Error abriendo la base de datos");
        return;
    }
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    sqlite3_bind_text(stmt, 1, movimiento.nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, movimiento.tipo, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, movimiento.potencia);
    sqlite3_bind_text(stmt, 4, movimiento.categoria, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, movimiento.efecto, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, movimiento.precision);
    sqlite3_bind_int(stmt, 7, movimiento.prioridad);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error ejecutando la consulta: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    }

// Función para insertar un objeto en la base de datos
void insertar_objeto(Objeto objeto) {
    char *sql = "INSERT INTO Objeto (nombre, cura, revivir, captura, subur, precio) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3 *db;
    sqlite3_stmt *stmt;
    
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        printf("Error abriendo la base de datos");
        return;
    }
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    sqlite3_bind_text(stmt, 1, objeto.nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, objeto.cura);
    sqlite3_bind_int(stmt, 3, objeto.revivir);
    sqlite3_bind_int(stmt, 4, objeto.captura);
    sqlite3_bind_int(stmt, 5, objeto.subur);
    sqlite3_bind_int(stmt, 6, objeto.precio);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error ejecutando la consulta: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    }

    void modificar_objeto(Objeto objeto) {
    char *sql = "UPDATE Objeto SET nombre = ?, cura = ?, revivir = ?, captura = ?, subur = ?, precio WHERE nombre = ?;";
    sqlite3 *db;
    sqlite3_stmt *stmt;
    
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        printf("Error abriendo la base de datos");
        return;
    }
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    sqlite3_bind_text(stmt, 1, objeto.nombre, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, objeto.cura);
    sqlite3_bind_int(stmt, 3, objeto.revivir);
    sqlite3_bind_int(stmt, 4, objeto.captura);
    sqlite3_bind_int(stmt, 5, objeto.subur);
    sqlite3_bind_int(stmt, 6, objeto.precio);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error ejecutando la consulta: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    }
    

   void modificar_movimiento(Movimiento movimiento) { 
    char *sql = "UPDATE Movimiento SET nombre = ?, tipo = ?, potencia = ?, categoria = ?, efecto = ?, precision = ?, prioridad = ? WHERE nombre = ?;";
    sqlite3 *db;
    sqlite3_stmt *stmt;
    
    if (sqlite3_open(obtener_valor_config("db_file"), &db) != SQLITE_OK) {
        printf("Error abriendo la base de datos");
        return;
    }
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    sqlite3_bind_text(stmt, 1, movimiento.nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, movimiento.tipo, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, movimiento.potencia);
    sqlite3_bind_text(stmt, 4, movimiento.categoria, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, movimiento.efecto, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, movimiento.precision);
    sqlite3_bind_int(stmt, 7, movimiento.prioridad);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Error ejecutando la consulta: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    
    }
   
