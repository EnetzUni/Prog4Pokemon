#include <stdio.h>

// Importamos los modulos
#include "moduloMenus.h"
#include "funciones.h"

void presentacion()
{
    printf( "  _____      _                                _____ \n");
    printf( " |  __ )    | |                              / ____|\n");
    printf( " | |__) |__ | | _____ _ __ ___   ___  _ __  | |     \n");
    printf( " |  ___/ _ )| |/ / _ ) '_  ` _ )/ _ )| '_  )| |     \n");
    printf( " | |  | (_) |   <  __/ | | | | | (_) | | | || |____ \n");
    printf( " |_|   (___/|_|)_)___|_| |_| |_|(___/|_| |_(_)_____|\n");
    printf( "\n\n");

    menuLoginRegistro();
}

void menuLoginRegistro()
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
                menuRegistro();
                return;
            } 
            else if (str[0] == '2')
            {
                printf("\n");
                menuLogin();
                return;
            }
    } while (str[0] != 'q');

}

void menuRegistro()
{
    char usuario[20];
    char contrasenya[20];

    imprimirTexto("\nRegistrar nuevo usuario:");

    printf("\n- Introduzca un nombre de usuario: ");
    fgets(usuario, sizeof(usuario), stdin);  // Leer entrada completa
    fflush(stdin); // Eliminar Buffer

    printf("\n- Introduzca una contrasenya: ");
    fgets(contrasenya, sizeof(contrasenya), stdin);  // Leer entrada completa
    fflush(stdin); // Eliminar Buffer

    // Aqui devemos meter las varibales usuario y contrasenya en la base de datos

    printf("\n");
    menuLoginRegistro();

}

void menuLogin()
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
    menuPrincipal();
}

void menuPrincipal()
{
    imprimirTexto("Menu Principal de Pokemon.c:\n-1: PC\n-2: Combate\n-q: Salir");
}