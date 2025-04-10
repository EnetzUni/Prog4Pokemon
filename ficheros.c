#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheros.h"

/**
 * Función para obtener un valor del archivo de configuración.
 * 
 * @param key Clave a buscar en el archivo.
 * @return Puntero a una cadena con el valor asociado a la clave (debe liberarse con free).
 */
char* obtener_valor_config(const char* key) {
    char* resultado = NULL;

    // 1. Definir la ruta del archivo de configuración
    char ruta[] = "Ficheros/Configuracion.txt";

    // 2. Abrir el archivo en modo lectura
    FILE* file = fopen(ruta, "r");
    if (file == NULL) {
        return NULL;  // Si no se puede abrir el archivo, retornar NULL
    }

    // 3. Leer línea por línea buscando la clave
    int c;
    char linea[256]; // Buffer
    int i = 0; // Índice buffer
    int seguir = 0;

    while (seguir != 1) { // Leer hasta el final
        c = fgetc(file);

        if (c == '\n' || c == EOF || i == 256 - 1) {
            linea[i] = '\0';  // Fin de cadena

            // Comprobar la key (clave)
            if (strncmp(linea, key, strlen(key)) == 0) {

                // 4. Si se encuentra la clave:

                //    - Ubicar la posición del '='
                char* pos_igual = strchr(linea, '=');
                
                if (pos_igual) {
                    //    - Determinar la longitud del valor
                    char* pos_valor = pos_igual + 1;  // Apuntar al primer carácter del valor
                    int longitud_valor = strlen(pos_valor); // Obtener la longitud del valor

                    //    - Reservar memoria con malloc
                    resultado = malloc(longitud_valor + 1); // +1 para el '\0'

                    //    - Copiar el valor en la memoria reservada
                    strcpy(resultado, pos_valor);

                    break;  // Si ya encontramos la clave, no necesitamos seguir buscando
                }
            }

            i = 0;  // Reiniciar índice
        } else {
            linea[i++] = c;  // Guardar carácter en el buffer
        }

        if(c == EOF){
            seguir = 1;
        }
    }

    // 5. Cerrar el archivo
    fclose(file);

    // 6. Devolver el valor. Si no se encuentra la clave, devolver NULL
    return resultado;
}

void escribirFiceroLog(char* texto) {

    //1. Abrir el archivo modo escritura
    FILE* file = fopen(obtener_valor_config("log_file"), "w"); 

    //2. Escribir el texto
    fprintf(file, texto);

    //3. Cerrar fichero
    fclose(file);
}
