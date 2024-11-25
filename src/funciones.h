#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>

typedef struct {
    int posicionX;
    int posicionY;
    int direccion;
    SDL_Texture *textura;
} Fantasma;

int** leeTablero(char *filename);
int tamanoFilas(int **tableroMatriz);
int tamanoColumnas(int **tableroMatriz);
int checking(int **tablero, int x, int y, int *HIGH_SCORE);
void imprimeMatriz(int **tableroMatriz);
void liberarMatriz(int **tableroMatriz);
void pacman(int x1, int y1, SDL_Renderer *renderer, SDL_Texture *pacmanRight1, SDL_Texture *pacmanRight2, 
            SDL_Texture *pacmanLeft1, SDL_Texture *pacmanLeft2,
            SDL_Texture *pacmanUp1, SDL_Texture *pacmanUp2, 
            SDL_Texture *pacmanDown1, SDL_Texture *pacmanDown2,
            int* estado, int direccion);

#endif // FUNCIONES_H