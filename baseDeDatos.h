#ifndef _BASEDEDATOS_H_ 
#define _BASEDEDATOS_H_

    typedef struct {
        char* nombre;
        char* tipo;
        int potencia;
        char*categoria;
        char* efecto;
        char** stats;
        int cant_stats;
        int precision;
        int prioridad;
    }  Movimiento;

    typedef struct {
        char* nombre;
        int vidaActual;
        int ps;
        char** tipos;
        int cant_tipo;
        int ataque;
        int defensa;
        int ataqueEspecial;
        int defensaEspecial;
        int velocidad;
        int nivel;
        int experiencia;
        int activo;
        Movimiento* movimientos;
    }  Pokemon;

    typedef struct {
        char* nombre;
        int cura;
        int revivir;
        int captura;
        int subur;
        int precio;
    }  Objeto;

    typedef struct {
        char* nombre;
        char* contrasena;
        int genero;
        int dinero;
        int nivelMaximo;
        int historia;
        Pokemon* pokemons;
        int cant_p;
        Objeto* objetos;
    }  Jugador;

    Jugador obtenerJugadorPorNombre(char* nombre);
    char* obtenerEfectoPorId(int id);
    char* obtenerStatPorId(int id);
    char* obtenerTipoPorId(int id);
    Pokemon* obtenerPokemons(int *cant_p);
    Pokemon obtenerPokemonsPorId(int id);
    Pokemon* obtenerPokemonJugador(int id_jugador, int *cant_p);
    Movimiento obtenerMovimientoPorId(int id);
    Movimiento* obtenerMovimientos(int *cant_m);
    int* obtenerIdStatPorIdMovimiento(int idMovimiento, int* cant_stat);
    char* obtenerCategoriaMovimientoPorId(int id);
    void insertar_jugador(Jugador jugador);
    void modificar_jugador(Jugador jugador);
    void insertar_pokemon(Pokemon pokemon);
    void modificar_pokemon(Pokemon pokemon);
    void insertar_movimiento(Movimiento movimiento);
    void insertar_objeto(Objeto objeto);
    void modificar_objeto(Objeto objeto);
    void modificar_movimiento(Movimiento movimiento);

#endif