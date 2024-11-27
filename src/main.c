#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include "ventana.h"
#include "funciones.h"
#include "audio.h"

int main(){
    
    int **tablero = leeTablero("tablero/tablero1.txt");
    ventanaJuego(tablero);
    liberarMatriz(tablero);
 
}
