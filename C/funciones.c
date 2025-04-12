#include <stdio.h>
#include <windows.h>  // Necesario para Sleep()

#include "funciones.h"

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