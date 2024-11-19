#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "audio.h"
#include "funciones.h"

void renderTablero(int **tablero, SDL_Window* initWindow, SDL_Renderer* renderer, SDL_Texture *pillChica, SDL_Texture *superPill, SDL_Texture *esqAbIzq, SDL_Texture *muroAb, SDL_Texture *muroIzq, SDL_Texture *muroDer, SDL_Texture *muroArriba, SDL_Texture *esqArribaIzq, SDL_Texture *esqArribaDer, SDL_Texture *esqAbDer, SDL_Texture *esq1, SDL_Texture *esq2, SDL_Texture *esq3, SDL_Texture *esq4){

    //necesito que la mierda de tablero se ajuste a la pantalla, asi que tengo que dividir segun el tamaño blabla
    
    int f = tamanoFilas(tablero);
    int c = tamanoColumnas(tablero);
    int anchoCelda = 448 / c;
    int altoCelda = 464 / f;
    int offsetY = 48;
    int offsetX = 16;

    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {

            SDL_Rect celda = {j * anchoCelda + offsetX, i * altoCelda + offsetY, anchoCelda, altoCelda};
            SDL_Texture *texturaActual = NULL;

            if (tablero[i][j] == 2){
                texturaActual = pillChica;
            }
            else if (tablero[i][j] == 3){
                texturaActual = superPill;
            }
            else if (tablero[i][j] == 4){
                texturaActual = esqAbIzq;
            }
            else if (tablero[i][j] == 5){
                texturaActual = muroAb;
            }
            else if (tablero[i][j] == 6){
                texturaActual = muroIzq;
            }
            else if (tablero[i][j] == 7){
                texturaActual = muroDer;
            }
            else if (tablero[i][j] == 8){
                texturaActual = muroArriba;
            }
            else if (tablero[i][j] == 9){
                texturaActual = esqArribaIzq;
            }
            else if (tablero[i][j] == 10){
                texturaActual = esqArribaDer;
            }
            else if (tablero[i][j] == 11){
                texturaActual = esqAbDer;
            }
            else if (tablero[i][j] == 12){
                texturaActual = esq1;
            }
            else if (tablero[i][j] == 13){
                texturaActual = esq2;
            }
            else if (tablero[i][j] == 14){
                texturaActual = esq3;
            }
            else if (tablero[i][j] == 15){
                texturaActual = esq4;
            }













            if (texturaActual != NULL) {
                SDL_RenderCopy(renderer, texturaActual, NULL, &celda);
            }
            else{
                // Si no hay textura, renderizar un color de fondo
                if (tablero[i][j] == 0) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
                } else if (tablero[i][j] == 1) {
                    SDL_SetRenderDrawColor(renderer, 25, 25, 166, 255); // Azul
                }
                SDL_RenderFillRect(renderer, &celda);
            }
        }
    }
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

void imagenVidas(SDL_Window *ventana, SDL_Renderer *renderer, SDL_Texture *pacmanReverseT, int vidas) {
    // Asegurarse de que la textura no sea NULL
    if (!pacmanReverseT) {
        printf("Error al cargar la textura pacmanReverse: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    // Definir el tamaño de la imagen
    SDL_Rect rectpacmanReverse;
    rectpacmanReverse.w = 24;  // Ancho de la imagen
    rectpacmanReverse.h = 24;  // Altura de la imagen

    // Bucle para dibujar las vidas
    for (int i = 0; i < vidas; i++) {
        // Establecer la posición de cada imagen de vida
        rectpacmanReverse.x = 30 + (i * (rectpacmanReverse.w + 5));  // Espaciado entre las imágenes
        rectpacmanReverse.y = 515;  // Coloca las imágenes en la parte inferior de la ventana

        // Renderizar la imagen en la posición correspondiente
        SDL_RenderCopy(renderer, pacmanReverseT, NULL, &rectpacmanReverse);
    }
}

void ventanaPrincipal(int **tablero, Uint32 flags) {
    const char *titulo = "Pac-man";
    int anchoP = 480;
    int altoP = 525+20;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
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
    
    SDL_Texture *pillChica = IMG_LoadTexture(renderer,"img/pillChica.png");
    if (!pillChica) {
        printf("Error al cargar la textura pillChica: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *superPill = IMG_LoadTexture(renderer, "img/superpill.png");

    if (!superPill) {
        printf("Error al cargar la textura superPill: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *pacmanReverse = IMG_LoadTexture(renderer, "img/pacmanreveres.png");

    if (!pacmanReverse) {
        printf("Error al cargar la textura pacmanReverse: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *esqAbIzq = IMG_LoadTexture(renderer, "img/esquinasAbajoIzq.png");
    if (!esqAbIzq) {
        printf("Error al cargar la textura esqAbIzq: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *muroAb = IMG_LoadTexture(renderer, "img/muroAbajo.png");
    if (!muroAb) {
        printf("Error al cargar la textura muroAbajo: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *muroIzq = IMG_LoadTexture(renderer, "img/muroIzq.png");
    if (!muroIzq) {
        printf("Error al cargar la textura muroIzq: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *muroDer = IMG_LoadTexture(renderer, "img/muroDerecha.png");

    if (!muroDer) {
        printf("Error al cargar la textura muroIzq: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *muroArriba = IMG_LoadTexture(renderer, "img/muroArriba.png");

    if (!muroArriba) {
        printf("Error al cargar la textura muroArriba: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }
    
    SDL_Texture *esqArribaIzq = IMG_LoadTexture(renderer, "img/esquinaArribaIzq.png");

    if (!muroArriba) {
        printf("Error al cargar la textura esqArribaIzq: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *esqArribaDer = IMG_LoadTexture(renderer, "img/esquinaArribaDer.png");

    if (!esqArribaDer) {
        printf("Error al cargar la textura esqArribaDer: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *esqAbDer = IMG_LoadTexture(renderer, "img/esqAbDer.png");

    if (!esqAbDer) {
        printf("Error al cargar la textura esqAbDer: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *esq1 = IMG_LoadTexture(renderer, "img/esq1.png");

    if (!esq1) {
        printf("Error al cargar la textura esq1: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *esq2 = IMG_LoadTexture(renderer, "img/esq2.png");

    if (!esq2) {
        printf("Error al cargar la textura esq2: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }
    
    SDL_Texture *esq3 = IMG_LoadTexture(renderer, "img/esq3.png");

    if (!esq3) {
        printf("Error al cargar la textura esq3: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }
    
    SDL_Texture *esq4 = IMG_LoadTexture(renderer, "img/esq4.png");

    if (!esq4) {
        printf("Error al cargar la textura esq4: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
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
    int vidas = 4;
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


        renderTablero(tablero, ventana, renderer, pillChica, superPill, esqAbIzq, muroAb, muroIzq, muroDer, muroArriba, esqArribaIzq, esqArribaDer, esqAbDer, esq1, esq2, esq3, esq4);
        imagenVidas(ventana, renderer, pacmanReverse, vidas);


        renderText(renderer, font, "1 UP", 20, 0);
        renderText(renderer, font, "HIGH SCORE", (anchoP - 110)/2, 0);

        renderText(renderer, font, texto, (anchoP-30)/2, 20);
        renderText(renderer, font, texto, (20), 20);
        
        HIGH_SCORE++;

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    //Liberar la textura después de usarla
    //Clean

    SDL_DestroyTexture(pacmanReverse);
    SDL_DestroyTexture(pillChica);
    TTF_CloseFont(font);
    SDL_FreeSurface(iconSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}