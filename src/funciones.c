#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "audio.h"

#define RIGHT 0
#define LEFT 1
#define UP 2 
#define DOWN 3

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
            printf("%d ", tableroMatriz[i][j]);
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

int distancia(int x1, int x2, int y1, int y2){
    return abs(x1-x2) + abs(y1-y2);
}

int checking(int **tablero, int x, int y, int *HIGH_SCORE){
    if(tablero[y][x] == 3 ){
        tablero[y][x] = 0;
        *HIGH_SCORE += 50;
        chomp("audio/eat_dot_0.wav", "audio/eat_dot_1.wav");
        return 1;
    }
    else if(tablero[y][x] == 0){
        return 1;
    }
    else if(tablero[y][x] == 2){
        tablero[y][x] = 0;
        *HIGH_SCORE += 10;
        chomp("audio/eat_dot_0.wav", "audio/eat_dot_1.wav");
        return 1;
    }
    else {
        return 0;
    }
}

void pacman(int x1, int y1, SDL_Renderer *renderer, SDL_Texture *pacmanRight1, SDL_Texture *pacmanRight2, 
            SDL_Texture *pacmanLeft1, SDL_Texture *pacmanLeft2,
            SDL_Texture *pacmanUp1, SDL_Texture *pacmanUp2, 
            SDL_Texture *pacmanDown1, SDL_Texture *pacmanDown2,
            int* estado, int direccion) {
    
    SDL_Rect pacmanRect = {x1, y1, 32, 32};  // Ajusta las dimensiones de Pac-Man
    SDL_Texture* currentTexture = NULL;

    // Selecciona la textura según la dirección y el estado de la boca
    switch (direccion) {
        case RIGHT:
            currentTexture = (*estado == 0) ? pacmanRight1 : pacmanRight2;
            break;
        case LEFT:
            currentTexture = (*estado == 0) ? pacmanLeft1 : pacmanLeft2;
            break;
        case UP:
            currentTexture = (*estado == 0) ? pacmanUp1 : pacmanUp2;
            break;
        case DOWN:
            currentTexture = (*estado == 0) ? pacmanDown1 : pacmanDown2;
            break;
    }

    // Renderizar el sprite actual
    SDL_RenderCopy(renderer, currentTexture, NULL, &pacmanRect);
    
    // Alternar el estado para la animación
    *estado = 1 - *estado;  // Cambiar entre 0 y 1
}