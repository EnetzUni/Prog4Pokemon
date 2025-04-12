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
                //menuLogin();
                return;
            }
    } while (str[0] != 'q');

}

void menuRegistro()
{
    imprimirTexto("Registrar nuevo usuario:\n");
}