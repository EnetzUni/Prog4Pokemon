#include <stdio.h>

// Importamos los modulos
#include "moduleMenus.h"
#include "db.h"

#include "string.h"

void imprimirTexto(char* texto)
{
    int i = 0;
    do
    {
        printf("%c",texto[i]);
        Sleep(30);
        i++;
    } while (texto[i] != '\0');
    printf("\n");
}

void presentation(sqlite3 *db, Jugador *jugadores)
{
    printf( "  _____      _                                _____ \n");
    printf( " |  __ )    | |                              / ____|\n");
    printf( " | |__) |__ | | _____ _ __ ___   ___  _ __  | |     \n");
    printf( " |  ___/ _ )| |/ / _ ) '_  ` _ )/ _ )| '_  )| |     \n");
    printf( " | |  | (_) |   <  __/ | | | | | (_) | | | || |____ \n");
    printf( " |_|   (___/|_|)_)___|_| |_| |_|(___/|_| |_(_)_____|\n");
    printf( "\n\n");

    menuLoginRegister(db, jugadores);
}

void menuLoginRegister(sqlite3 *db, Jugador *jugadores)
{

    imprimirTexto("Menu de Registro/Log in\n-1: Registrarse\n-2: Iniciar Sesion\n-q: Salir");

    char str[2];

    do
    {
            printf("\n- Opcion: ");
            fgets(str, sizeof(str), stdin);  // Leer entrada completa
            fflush(stdin); // Eliminar Buffer

            if(str[0] == '1')
            {
                printf("\n");
                menuRegister(db, jugadores);
                return;
            } 
            else if (str[0] == '2')
            {
                printf("\n");
                menuLogin(db, jugadores);
                return;
            }
    } while (str[0] != 'q');

}

void menuRegister(sqlite3 *db, Jugador *jugadores)
{
    char usuario[50];
    char contrasenya[50];
    char genero[4];
    imprimirTexto("\nRegistrar nuevo usuario:");

    printf("\n- Introduzca un nombre de usuario: ");
    fgets(usuario, sizeof(usuario), stdin);
    usuario[strcspn(usuario, "\n")] = '\0';  // Eliminar '\n' final

    printf("\n- Introduzca una contrasenya: ");
    fgets(contrasenya, sizeof(contrasenya), stdin);
    contrasenya[strcspn(contrasenya, "\n")] = '\0';

    printf("\n- Introduzca su genero (M/F): ");
    fgets(genero, sizeof(genero), stdin);
    genero[strcspn(genero, "\n")] = '\0';

    printf("usuario = '%s'\n", usuario);
    printf("contrasenya = '%s'\n", contrasenya);
    printf("genero = '%s'\n", genero);

    // Introducimos en la tabla Jugador el nuevo usuario                                (!) COMPROBAR SI YA EXISTE EL JUGADOR
    insertar_jugador(db, 00001, usuario, contrasenya, genero, 1000, 5, jugadores, 51);

    printf("\n");
    menuLoginRegister(db, jugadores);

}

void menuLogin(sqlite3 *db, Jugador *jugadores)
{
    char usuario[20];
    char contrasenya[20];

    imprimirTexto("\nIniciar sesion con una cuenta registrada:");

    printf("\n- Introduzca su nombre de usuario: ");
    fgets(usuario, sizeof(usuario), stdin);  // Leer entrada completa
    fflush(stdin); // Eliminar Buffer

    printf("\n- Introduzca su contrasenya: ");
    fgets(contrasenya, sizeof(contrasenya), stdin);  // Leer entrada completa
    fflush(stdin); // Eliminar Buffer

    // Aqui tenemos que checkear con la base de datos y en caso positivo continuar
    // y en caso negativo volver a preguntar

    // Por el momento continuaremos

    printf("\n");
    menuPrincipal(db, jugadores);
}

void menuPrincipal(sqlite3 *db, Jugador *jugadores)
{
    imprimirTexto("Menu Principal de Pokemon.c:\n-1: PC\n-2: Combate\n-q: Salir");
}