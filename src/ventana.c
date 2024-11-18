#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "audio.h"
#include "funciones.h"

void renderTablero(int **tablero, SDL_Window* initWindow, SDL_Renderer* renderer){

    //necesito que la mierda de tablero se ajuste a la pantalla, asi que tengo que dividir segun el tamaño blabla
    
    int f = tamanoFilas(tablero);
    int c = tamanoColumnas(tablero);
    int anchoCelda = 538 / c;
    int altoCelda = 691 / f;
    int offsetY=45;

    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            SDL_Rect celda = {j * anchoCelda, i * altoCelda + offsetY, anchoCelda, altoCelda};

            // Cambiar el color dependiendo del valor de la celda
            if (tablero[i][j] == 0 ){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            else if (tablero[i][j] == 1) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255);
            } 
            else if (tablero[i][j] == 2){
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            }

            // Dibujar la celda
            SDL_RenderFillRect(renderer, &celda);
        }
    }
    SDL_RenderPresent(renderer);
}

void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y){
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL) {
        printf("Error al crear la superficie de texto: %s\n", TTF_GetError());
        return;
    }
 
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    SDL_DestroyTexture(texture);
}


void ventanaPrincipal(int **tablero, Uint32 flags) {
    const char *titulo = "Pac-man";
    int anchoP = 532;
    int altoP = 750;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) == -1){
        printf("No se pudo inicializar IMG_Init: %s\n", IMG_GetError());
    }

    if (TTF_Init() == -1) {
        printf("No se pudo inicializar SDL_ttf: %s\n", TTF_GetError());
        return;
    }

    SDL_Window* ventana = SDL_CreateWindow(titulo, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, anchoP, altoP, flags);
    if (!ventana) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Surface *iconSurface = IMG_Load("img/Pacman.png"); // Asegúrate de que la ruta sea correcta
    if (!iconSurface) {
        printf("No se pudo cargar la imagen del icono: %s\n", IMG_GetError());
        SDL_DestroyWindow(ventana);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    TTF_Font *font = TTF_OpenFont("font/ARCADECLASSIC.ttf", 24);
    if (font == NULL) {
        printf("No se pudo cargar la fuente: %s\n", TTF_GetError());
        return;
    }



    // Bucle principal

    int HIGH_SCORE = 0;
    int ejecutando = 1;
    SDL_Event evento;
    SDL_SetWindowIcon(ventana, iconSurface);

    while (ejecutando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                ejecutando = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        char texto[50];
        snprintf(texto, sizeof(texto), "%d", HIGH_SCORE);


        renderTablero(tablero, ventana, renderer);
        renderText(renderer, font, "1 UP", 20, 0);
        renderText(renderer, font, "HIGH SCORE", (anchoP - 110)/2, 0);

        renderText(renderer, font, texto, (anchoP-30)/2, 20);
        renderText(renderer, font, texto, (20), 20);
        
        HIGH_SCORE++;

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }


    //clean
    TTF_CloseFont(font);
    SDL_FreeSurface(iconSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}