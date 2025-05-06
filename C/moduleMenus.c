#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "string.h"

// Importamos los modulos
#include "moduleMenus.h"
#include "db.h"

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

void presentation(sqlite3 *db)
{
    printf( "  _____      _                                _____ \n");
    printf( " |  __ )    | |                              / ____|\n");
    printf( " | |__) |__ | | _____ _ __ ___   ___  _ __  | |     \n");
    printf( " |  ___/ _ )| |/ / _ ) '_  ` _ )/ _ )| '_  )| |     \n");
    printf( " | |  | (_) |   <  __/ | | | | | (_) | | | || |____ \n");
    printf( " |_|   (___/|_|)_)___|_| |_| |_|(___/|_| |_(_)_____|\n");
    printf( "\n\n");

    menuLoginRegister(db);
}

void menuLoginRegister(sqlite3 *db)
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
                menuRegister(db);
                return;
            } 
            else if (str[0] == '2')
            {
                printf("\n");
                menuLogin(db);
                return;
            }
    } while (str[0] != 'q');

}

void menuRegister(sqlite3 *db)
{
    char nickname[50];
    char password[50];
    char genderC[4];
    imprimirTexto("\nRegistrar nuevo usuario:");

    printf("\n- Introduzca un nickname: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = '\0';  // Eliminar '\n' final

    printf("\n- Introduzca una contrasenya: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("\n- Introduzca su genero (M/F): ");
    fgets(genderC, sizeof(genderC), stdin);
    genderC[strcspn(genderC, "\n")] = '\0';

    bool genderB = 0; // Convertir a boolean
    if (genderC == "F")
    {
        genderB == 1;
    }

    printf("nickname = '%s'\n", nickname);
    printf("password = '%s'\n", password);
    printf("gender = '%s'\n", genderC);

    // Introducimos en la tabla Player el nuevo nickname                                (!) COMPROBAR SI YA EXISTE EL JUGADOR
    if(checkPlayer(db, nickname) == 1){
        printf("THIS SHIT WORKS!!");
    }
    insertPlayer(db, nickname, password, genderB, 10, 1);

    printf("\n");
    menuLoginRegister(db);

}

void menuLogin(sqlite3 *db)
{
    char nickname[20];
    char password[20];

    imprimirTexto("\nIniciar sesion con una cuenta registrada:");

    printf("\n- Introduzca su nombre de usuario: ");
    fgets(nickname, sizeof(nickname), stdin);  // Leer entrada completa
    fflush(stdin); // Eliminar Buffer

    printf("\n- Introduzca su contrasenya: ");
    fgets(password, sizeof(password), stdin);  // Leer entrada completa
    fflush(stdin); // Eliminar Buffer

    // Aqui tenemos que checkear con la base de datos y en caso positivo continuar
    // y en caso negativo volver a preguntar

    // Por el momento continuaremos

    printf("\n");
    menuPrincipal(db);
}

void menuPrincipal(sqlite3 *db)
{
    imprimirTexto("Menu Principal de Pokemon.c:\n-1: PC\n-2: Combate\n-q: Salir");
}