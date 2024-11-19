#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "ventana.h"
#include "funciones.h"


int main(){
    
    int **tablero = leeTablero("tablero/tablero1.txt");
    int filas = tamanoFilas(tablero);
    int columnas = tamanoColumnas(tablero);

    //por simplicidad se asume en la matriz 0=celda vacia, 1=celda con punto, 2=muro

    ventanaPrincipal(tablero, SDL_WINDOW_SHOWN);
    imprimeMatriz(tablero);
    printf("filas = %d, columnas = %d\n", filas, columnas);
    liberarMatriz(tablero);

}