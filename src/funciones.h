#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>

int** leeTablero(char *filename);
int tamanoFilas(int **tableroMatriz);
int tamanoColumnas(int **tableroMatriz);
int checking(int **tablero, int x, int y, int *HIGH_SCORE,int *pill_time);
void imprimeMatriz(int **tableroMatriz);
void liberarMatriz(int **tableroMatriz);
int obtenerDireccionRandom(Uint32 *ultimoTiempo);

void pacman(int x1, int y1, SDL_Renderer *renderer, SDL_Texture *pacmanRight1, SDL_Texture *pacmanRight2, 
            SDL_Texture *pacmanLeft1, SDL_Texture *pacmanLeft2,
            SDL_Texture *pacmanUp1, SDL_Texture *pacmanUp2, 
            SDL_Texture *pacmanDown1, SDL_Texture *pacmanDown2,
            int* estado, int direccion, Uint32* lastTime,int colision);

void moverFantasma(SDL_Renderer *renderer, SDL_Texture* blinkyRight1, SDL_Texture* blinkyRight2, 
                   SDL_Texture* blinkyLeft1, SDL_Texture* blinkyLeft2, 
                   SDL_Texture* blinkyUp1, SDL_Texture* blinkyUp2, 
                   SDL_Texture* blinkyDown1, SDL_Texture* blinkyDown2, 
                   int *blinkyX, int *blinkyY, int *direccionBlinky, int *blinkyEstado, 
                   Uint32 *ticks, int *coorX, int *coorY, int **tablero, int anchoP, int altoP);

#endif // FUNCIONES_H