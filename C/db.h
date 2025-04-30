#ifndef DB_H
#define DB_H

#include "sqlite3.h"

typedef struct {
    int id;
    char name[50];
    char type1[50];
    char type2[50];
    int PS;
    int ataque;
    int defensa;
    int ataqueESP;
    int defensaESP;
    int velocidad;
} Pokemon;

typedef struct {
    int id;
    char name[50];
    char password[50];
    char genero[1];
    int dinero;
    int maxLVL;
} Jugador;

typedef struct {
    int id;
    char name[50];
    int cura;
    int revivir;
    int captura;
    int subida;
} Objeto;

typedef struct {
    int id;
    int idTipo;
    int idCategoriaMov;
    char name[50];
    int potencia;
    int precision;
    int prioridad;
} Movimiento;


// Funciones para obtener datos
int cargar_pokemons(sqlite3 *db, Pokemon *pokemons, int max);
int cargar_jugadores(sqlite3 *db, Jugador *jugadores, int max);
int cargar_objetos(sqlite3 *db, Objeto *objetos, int max);
int cargar_movimientos(sqlite3 *db, Movimiento *movs, int max);
int insertar_jugador(sqlite3 *db, int id, const char *name, const char *password, const char *genero, int dinero, int maxLVL, Jugador *jugadores, int max);


#endif