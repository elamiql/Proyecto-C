#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int filas;
int columnas;


int** leeTablero(char *filename) {
    FILE *tablero1 = fopen(filename, "r");
    
    if (tablero1 == NULL) {
        printf("Error al leer el archivo\n");
        return NULL;
    }

    char linea[80];
    filas = 0;
    columnas = 0;

    while (fgets(linea, sizeof(linea), tablero1)) {
        filas++;
        if (filas == 1) {

            char *token = strtok(linea, " ");
            while (token != NULL) {
                columnas++;
                token = strtok(NULL, " ");
            }
        }
    }

    rewind(tablero1);

    int **tableroMatriz = (int **)malloc(filas * sizeof(int *));
    if (tableroMatriz == NULL) {
        printf("Error al asignar memoria para las filas.\n");
        fclose(tablero1);
        return NULL;
    }

    for (int i = 0; i < filas; i++) {
        tableroMatriz[i] = (int *)malloc(columnas * sizeof(int));
        if (tableroMatriz[i] == NULL) {
            printf("Error al asignar memoria para las columnas.\n");
            fclose(tablero1);
            return NULL;
        }
    }

    int i = 0;
    while (fgets(linea, sizeof(linea), tablero1) != NULL) {
        char *token = strtok(linea, " ");
        int j = 0;
        while (token != NULL && j < columnas) {
            tableroMatriz[i][j] = atoi(token);
            token = strtok(NULL, " ");
            j++;
        }
        i++;
    }
    fclose(tablero1);
    return tableroMatriz;
}

void imprimeMatriz(int **tableroMatriz) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%2d ", tableroMatriz[i][j]);
        }
        printf("\n");
    }
}

int tamanoFilas(int **tableroMatriz) {
    return filas;
}

int tamanoColumnas(int **tableroMatriz) {
    return columnas;
}

void liberarMatriz(int **tableroMatriz) {
    for (int i = 0; i < filas; i++) {
        free(tableroMatriz[i]);
    }
    free(tableroMatriz);
}

//funcion que crea al pacman, int a y b son los lugares donde va a aparecer
void pacman(int a, int b, SDL_Renderer *renderer, SDL_Texture *pacmanPlayer){
    // Definir el tamaño de la imagen
    SDL_Rect pacman;
    pacman.w = 32;  // Ancho de la imagen
    pacman.h = 32;  // Altura de la imagen
    pacman.x = a; // Multiplicar la posición inicial por la velocidad
    pacman.y = b; // Hacer lo mismo en Y, si aplica

    SDL_RenderCopy(renderer, pacmanPlayer, NULL, &pacman);
}

void fantasma(int a, int b, SDL_Renderer *renderer, SDL_Texture *pacmanReverseT){
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"0");
    SDL_Rect fantasma;
    fantasma.w = 27;
    fantasma.h = 27;
    fantasma.x = a;
    fantasma.y = b;
    SDL_RenderCopy(renderer, pacmanReverseT,NULL,&fantasma);
    SDL_RenderPresent(renderer);
}
