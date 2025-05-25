#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "string.h"
#include "stdlib.h"
#include <ctype.h>

// Importamos los modulos
#include "moduleMenus.h"
#include "db.h"
#include "player.h"
#include "pc.h"
#include "type.h"

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

void presentation(sqlite3 *db, char* nicknameAdmin)
{
    printf( "  _____      _                                _____ \n");
    printf( " |  __ )    | |                              / ____|\n");
    printf( " | |__) |__ | | _____ _ __ ___   ___  _ __  | |     \n");
    printf( " |  ___/ _ )| |/ / _ ) '_  ` _ )/ _ )| '_  )| |     \n");
    printf( " | |  | (_) |   <  __/ | | | | | (_) | | | || |____ \n");
    printf( " |_|   (___/|_|)_)___|_| |_| |_|(___/|_| |_(_)_____|\n");
    printf( "\n\n");

    menuLoginRegister(db, nicknameAdmin);
}

void menuLoginRegister(sqlite3 *db, char* nicknameAdmin)
{
    imprimirTexto("Menu de Registro/Log in\n-1: Registrarse\n-2: Iniciar Sesion\n-3: Iniciar Sesion como Administrador\n-q: Salir");

    char str[2];

    printf("\n- Opcion: ");
    fgets(str, sizeof(str), stdin);  // Leer entrada completa
    fflush(stdin); // Eliminar Buffer

    if (str[0] == 'q') // Salir de aplicacion
    {
        return;
    }

    if(str[0] == '1') // Opcion: Registrar nuevo usuario
    {
        printf("\n");
        menuRegister(db, nicknameAdmin);
        return;
    } 
    else if (str[0] == '2') // Opcion: Inciar Sesion
    {
        printf("\n");
        menuLogin(db, nicknameAdmin);
        return;
    }
    else if (str[0] == '3') // Opcion: Inciar Sesion como Administrador
    {
        printf("\n");
        Player* player = loadPlayer(db, nicknameAdmin);
        menuPrincipal(db, player); // Accede al Menu Principal
        return;
    }

    if (str[0] != 'q') // Excepcion: campo no valido ingresado
    {
        imprimirTexto("\nPor favor ingrese una opcion valida.\n");
        menuLoginRegister(db, nicknameAdmin);
    }
    

}

void menuRegister(sqlite3 *db, char* nicknameAdmin)
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

    printf("\n- Introduzca su genero (M/F): "); // Por defecto el genero asignado sera Male
    fgets(genderC, sizeof(genderC), stdin);
    genderC[strcspn(genderC, "\n")] = '\0';

    bool genderB = 0; // Convertir a boolean
    if (genderC == "F")
    {
        genderB == 1;
    }


    // Introducimos en la tabla Player el nuevo nickname // 

    if(checkPlayer(db, nickname) == 1) // Excepcion: ya existe una cuenta registrada con el mismo nickname
    { 
        imprimirTexto("\nYa existe un cuenta registrada con ese nickname, elige una opcion.");
    }else if (strlen(nickname) == 0 || strlen(password) == 0) // Excepcion: alguno de los parametros insertados esta vacio
    {
        imprimirTexto("\nNinguno de los parametros puede estar vacio, elige una opcion.");
    } else 
    {
        PokemonPlayer* listPokemon[6];
        Player* newPlayer = createPlayer(nickname, password, genderB, listPokemon, 0, 0, 0);
        
        insertPlayer(db, newPlayer); // Insertar judador
    }

    printf("\n");
    menuLoginRegister(db, nicknameAdmin);

}

void menuLogin(sqlite3 *db, char* nicknameAdmin)
{
    char nickname[20];
    char password[20];

    imprimirTexto("\nIniciar sesion con una cuenta registrada:");

    printf("\n- Introduzca su nombre de usuario: ");
    fgets(nickname, sizeof(nickname), stdin);  // Leer entrada completa
    nickname[strcspn(nickname, "\n")] = '\0';  // Eliminar '\n' final

    printf("\n- Introduzca su contrasenya: ");
    fgets(password, sizeof(password), stdin);  // Leer entrada completa
    password[strcspn(password, "\n")] = '\0';


    // Comprobar si existe una cuenta con ese usuario y contraseña // 

    if(strlen(nickname) == 0 || strlen(password) == 0) // Excepcion: alguno de los parametros insertados esta vacio
    { 
        imprimirTexto("\nNinguno de los parametros puede estar vacio, elige una opcion.");
        printf("\n");
        menuLoginRegister(db, nicknameAdmin);
    }else if (checkPassword(db, nickname, password)) // Existe una cuenta con ese usuario y contraseña
    {
        imprimirTexto("\nIniciado Sesion Correctamente!\n");
        Player* player = loadPlayer(db, nickname);
        menuPrincipal(db, player); // Accede al Menu Principal
    }else if (checkPassword(db, nickname, password) == 0) // Existe una cuenta con ese usuario y contraseña
    {
        imprimirTexto("\nUsuario o contrasenya incorrectos, elige una opcion.");
        printf("\n");
        menuLoginRegister(db, nicknameAdmin);
    }
    
}

void menuPrincipal(sqlite3 *db, Player* player)
{
    char str[2];

    imprimirTexto("Menu Principal de Pokemon.c:\n-1: PC\n-2: Combate\n-q: Salir");

    printf("\n- Opcion: ");
    fgets(str, sizeof(str), stdin);  // Leer entrada completa
    fflush(stdin); // Eliminar Buffer

    if (str[0] == 'q') // Salir de aplicacion
    {
        return;
    }

    if(str[0] == '1') // Opcion: Ingresar a PC
    {
        printf("\n");
        menuPC(db, player);
        return;
    } 
    else if (str[0] == '2') // Opcion: Iniciar Combate
    {
        printf("\n");
        combate(db, player);
        return;
    }

    if (str[0] != 'q') // Excepcion: campo no valido ingresado
    {
        imprimirTexto("\nPor favor ingrese una opcion valida.\n");
        menuPrincipal(db, player);
    }

    return;
}

void menuPC(sqlite3 *db, Player* player)
{
    PC* pc = loadPc(db, player->nickname);
    char str[2];

    imprimirTexto("Has ingresado a PC:\n-1: Sacar Pokemon a Equipo\n-2: Dejar Pokemon en PC\n-3: Ver PC\n-4: Ver Equipo\n-q: Salir");

    printf("\n- Opcion: ");
    fgets(str, sizeof(str), stdin);  // Leer entrada completa
    fflush(stdin); // Eliminar Buffer

    if (str[0] == 'q') // Salir de aplicacion
    {
        menuPrincipal(db, player);
    }

    if(str[0] == '1') // Opcion: Sacar Pokemon a Equipo
    {
        printf("\n");
        printPc(pc);
        char str2[3];
        int opcion = 1;  

        printf("\n- Opcion: ");
        fgets(str2, sizeof(str2), stdin);
        fflush(stdin);

        if (isdigit(str2[0])) {
            int temp = atoi(str2);
            if (temp >= 1 && temp <= pc->pcListSize) {
                opcion = temp;
            } else {
                imprimirTexto("Campo ingresado no valido, repita la operacion.\n");
                menuPC(db, player);
                return;
            }
                // Player Pokemon
                PokemonPlayer* pokemonPlayer = pc->pcList[opcion - 1];
                removePcPokemonPlayer(db, pc, opcion);
                addPlayerPokemonPlayer(db, player, pokemonPlayer);
                imprimirTexto("Pokemon añadido al Equipo correctamente.\n");
                menuPC(db, player);
        } else {
            imprimirTexto("Campo ingresado no valido, repita la operacion.\n");
            menuPC(db, player);
        }

        return;
    } 
    else if (str[0] == '2') // Opcion: Dejar pokemon en PC
    {
        printf("\n");
        printTeam(player);
        char str2[3];
        int opcion = 1;  

        printf("\n- Opcion: ");
        fgets(str2, sizeof(str2), stdin);
        fflush(stdin);

        if (isdigit(str2[0])) {
            int temp = atoi(str2);
            if (temp >= 1 && temp <= player->listPokemonSize) {
                opcion = temp;
            } else {
                imprimirTexto("Campo ingresado no valido, repita la operacion.\n");
                menuPC(db, player);
                return;
            }
                // Player Pokemon
                PokemonPlayer* pokemonPlayer = player->listPokemon[opcion - 1];
                removePlayerPokemonPlayer(db, player, opcion);
                addPcPokemonPlayer(db, pc, pokemonPlayer);
                imprimirTexto("Pokemon añadido al PC correctamente.\n");
                menuPC(db, player);
        } else {
            imprimirTexto("Campo ingresado no valido, repita la operacion.\n");
            menuPC(db, player);
        }

        return;
    }
    else if (str[0] == '3') // Opcion: Ver PC
    {
        printf("\n");
        printPc(pc);
        menuPC(db, player);
        return;
    }
    else if (str[0] == '4') // Opcion: Ver Equipo
    {
        printf("\n");
        printTeam(player);
        menuPC(db, player);      
        return;
    }

    if (str[0] != 'q') // Excepcion: campo no valido ingresado
    {
        imprimirTexto("\nPor favor ingrese una opcion valida.\n");
        menuPC(db, player);
    }

    return;
}

void combate(sqlite3 *db, Player* player)
{
    imprimirTexto("Te adentras a una zona de hierva alta . . . Un pokemon salvaje ha aparecido!\n");
    imprimirTexto("Que pokemon quieres sacar de tu equipo?");
    
    printTeam(player);

    char str[3];
    int opcion = 1;  

    printf("\n- Opcion: ");
    fgets(str, sizeof(str), stdin);
    fflush(stdin);

    if (isdigit(str[0])) {
        int temp = atoi(str);
        if (temp >= 1 && temp <= player->listPokemonSize) {
            opcion = temp;
        }
    }
    // Player Pokemon
    PokemonPlayer* pokemonPlayer = player->listPokemon[opcion - 1];

    PokemonPlayerBattle* pokemonPlayerBattle = createPokemonPlayerBattle(pokemonPlayer);

    // Wild Pokemon
    Pokemon* randomPokemon = loadPokemon(db, ((rand() % 649) + 1));
    Movement** movementWild = createRandomMovementList(db);
    PokemonPlayer* pokemonWild = createPokemonPlayer(randomPokemon, 0, randomPokemon->name, movementWild, 4, player->maxLvL, calculateBattleHp(randomPokemon->hp, calculateLvl(player->maxLvL)), (Status) NULL);
    PokemonPlayerBattle* pokemonWildBattle = createPokemonPlayerBattle(pokemonWild);

    if(pokemonWildBattle->battleSpeed > pokemonPlayerBattle->battleSpeed)
    {
        while (pokemonWildBattle->pokemonPlayer->curHp != 0 || pokemonPlayerBattle->pokemonPlayer->curHp != 0)
        {
            Movement* wildMovementSelection = pokemonWildBattle->pokemonPlayer->listMovement[((rand() % pokemonWildBattle->pokemonPlayer->listMovementSize) + 1)];
            combatAttack(pokemonWildBattle, pokemonPlayerBattle, wildMovementSelection);

            if(pokemonPlayerBattle->pokemonPlayer->curHp != 0) {
                for (int i = 0; i < pokemonPlayerBattle->pokemonPlayer->listMovementSize; i++)
                {
                    printf("----- Movimiento #%d -----\n", i + 1);
                    printMovementSmall(pokemonPlayerBattle->pokemonPlayer->listMovement[i]);
                }
                char str2[3];
                int opcion = 1;  

                printf("\n- Opcion: ");
                fgets(str2, sizeof(str2), stdin);
                fflush(stdin);

                if (isdigit(str2[0])) {
                    int temp = atoi(str2);
                    if (temp >= 1 && temp <= pokemonPlayerBattle->pokemonPlayer->listMovementSize) {
                        opcion = temp;
                    } 
                }

                Movement* playerMovementSelection = pokemonPlayerBattle->pokemonPlayer->listMovement[opcion - 1];
                combatAttack(pokemonPlayerBattle, pokemonWildBattle, playerMovementSelection);

            }
        }
    } else {
        while (pokemonWildBattle->pokemonPlayer->curHp != 0 || pokemonPlayerBattle->pokemonPlayer->curHp != 0)
        {
            for (int i = 0; i < pokemonPlayerBattle->pokemonPlayer->listMovementSize; i++)
            {
                printf("----- Movimiento #%d -----\n", i + 1);
                printMovementSmall(pokemonPlayerBattle->pokemonPlayer->listMovement[i]);
            }

            char str2[3];
            int opcion = 1;

            printf("\n- Opcion: ");
            fgets(str2, sizeof(str2), stdin);
            fflush(stdin);

            if (isdigit(str2[0])) {
                int temp = atoi(str2);
                if (temp >= 1 && temp <= pokemonPlayerBattle->pokemonPlayer->listMovementSize) {
                    opcion = temp;
                } 
            }

            Movement* playerMovementSelection = pokemonPlayerBattle->pokemonPlayer->listMovement[opcion - 1];
            combatAttack(pokemonPlayerBattle, pokemonWildBattle, playerMovementSelection);

            if(pokemonPlayerBattle->pokemonPlayer->curHp != 0) {
                Movement* wildMovementSelection = pokemonWildBattle->pokemonPlayer->listMovement[((rand() % pokemonWildBattle->pokemonPlayer->listMovementSize) + 1)];
                combatAttack(pokemonWildBattle, pokemonPlayerBattle, wildMovementSelection);
            }
        }

    }

    return;
}