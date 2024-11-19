#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "audio.h"
#include "funciones.h"

void renderTablero(int **tablero, SDL_Window* initWindow, SDL_Renderer* renderer, SDL_Texture *pillChica, SDL_Texture *superPill){

    //necesito que la mierda de tablero se ajuste a la pantalla, asi que tengo que dividir segun el tamaño blabla
    
    int f = tamanoFilas(tablero);
    int c = tamanoColumnas(tablero);
    int anchoCelda = 560 / c;
    int altoCelda = 560 / f;
    int offsetY = 45;

    if (!pillChica){
        printf("Error al cargar las texturas: %s", SDL_GetError());
        return;
    }

    if (!superPill){
        printf("Error al cargar las texturas: %s", SDL_GetError());
        return;
    }


    for (int i = 0; i < f; i++) {
        for (int j = 0; j < c; j++) {
            SDL_Rect celda = {j * anchoCelda, i * altoCelda + offsetY, anchoCelda, altoCelda};

            // Cambiar el color dependiendo del valor de la celda
            // 0 = vacio, 1 = muro, 2 = pill chica, 3 = pill grande, 4 = cherry, ... etc,

            SDL_Texture *texturaActual = NULL;

            if (tablero[i][j] == 2){
                texturaActual = pillChica;
            }
            else if(tablero[i][j] == 3){
                texturaActual = superPill;
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

    // Definir el tamaño de la imagen
    SDL_Rect rectpacmanReverse;
    rectpacmanReverse.w = 20;  // Ancho de la imagen
    rectpacmanReverse.h = 20;  // Altura de la imagen

    // Bucle para dibujar las vidas
    for (int i = 0; i < vidas; i++) {
        // Establecer la posición de cada imagen de vida
        rectpacmanReverse.x = 30 + (i * (rectpacmanReverse.w + 5));  // Espaciado entre las imágenes
        rectpacmanReverse.y = 603;  // Coloca las imágenes en la parte inferior de la ventana

        // Renderizar la imagen en la posición correspondiente
        SDL_RenderCopy(renderer, pacmanReverseT, NULL, &rectpacmanReverse);
    }
}

void ventanaPrincipal(int **tablero, Uint32 flags) {
    const char *titulo = "Pac-man";
    int anchoP = 560;
    int altoP = 630;

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
        printf("Error al cargar la textura pillChica: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_Texture *pacmanReverse = IMG_LoadTexture(renderer, "img/pacmanreveres.png");

    if (!pacmanReverse) {
        printf("Error al cargar la textura pillChica: %s\n", IMG_GetError());
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
    int vidas = 5;
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


        renderTablero(tablero, ventana, renderer, pillChica, superPill);
        imagenVidas(ventana, renderer, pacmanReverse, vidas);


        renderText(renderer, font, "1 UP", 20, 0);
        renderText(renderer, font, "HIGH SCORE", (anchoP - 110)/2, 0);

        renderText(renderer, font, texto, (anchoP-30)/2, 20);
        renderText(renderer, font, texto, (20), 20);
        
        HIGH_SCORE++;

        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
        vidas--;
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