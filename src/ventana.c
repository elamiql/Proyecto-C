#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "audio.h"
#include "funciones.h"

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

#define pacmanSpeed 130


const int offsetY = 48 -16*2;
const int offsetX = 16;


SDL_Texture* cargarTextura(SDL_Renderer* renderer, const char* ruta) {
    SDL_Texture* textura = IMG_LoadTexture(renderer, ruta);
    if (!textura) {
        printf("Error al cargar la textura %s: %s\n", ruta, IMG_GetError());
    }
    return textura;
}

void renderTablero(int **tablero, SDL_Window* initWindow, SDL_Renderer* renderer, SDL_Texture *pillChica, SDL_Texture *superPill, SDL_Texture *esqAbIzq, SDL_Texture *muroAb, SDL_Texture *muroIzq, SDL_Texture *muroDer, SDL_Texture *muroArriba, SDL_Texture *esqArribaIzq, SDL_Texture *esqArribaDer, SDL_Texture *esqAbDer, SDL_Texture *esq1, SDL_Texture *esq2, SDL_Texture *esq3, SDL_Texture *esq4, SDL_Texture *muroVert1, SDL_Texture *muroVert2, SDL_Texture *muroHor1, SDL_Texture *muroHor2, SDL_Texture *esq4_2, SDL_Texture *esq3_2, SDL_Texture *esq1_2, SDL_Texture *esq2_2, SDL_Texture *interseccion1, SDL_Texture *interseccion2, SDL_Texture *interseccion3, SDL_Texture *interseccion4, SDL_Texture *interseccion5, SDL_Texture *interseccion6, SDL_Texture *esq90g1, SDL_Texture *esq90g2, SDL_Texture *esq90g3, SDL_Texture *esq90g4, SDL_Texture *borde1, SDL_Texture *borde2, SDL_Texture *rosado){

    int f = tamanoFilas(tablero);
    int c = tamanoColumnas(tablero);
    int anchoCelda = 448 / c;
    int altoCelda = 496 / f;

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
            else if (tablero[i][j] == 16){
                texturaActual = muroVert1;
            }
            else if (tablero[i][j] == 17){
                texturaActual = muroVert2;
            }
            else if (tablero[i][j] == 18){
                texturaActual = muroHor1;
            }
            else if (tablero[i][j] == 19){
                texturaActual = muroHor2;
            }
            else if (tablero[i][j] == 20){
                texturaActual = esq4_2;
            }
            else if (tablero[i][j] == 21){
                texturaActual = esq3_2;
            }
            else if (tablero[i][j] == 22){
                texturaActual = esq1_2;
            }
            else if (tablero[i][j] == 23){
                texturaActual = esq2_2;
            }
            else if (tablero[i][j] == 24){
                texturaActual = interseccion1;
            }
            else if (tablero[i][j] == 25){
                texturaActual = interseccion2;
            }
            else if (tablero[i][j] == 26){
                texturaActual = interseccion3;
            }
            else if (tablero[i][j] == 27){
                texturaActual = interseccion4;
            }
            else if (tablero[i][j] == 28){
                texturaActual = interseccion5;
            }
            else if (tablero[i][j] == 29){
                texturaActual = interseccion6;
            }
            else if (tablero[i][j] == 30){
                texturaActual = esq90g1;
            }
            else if (tablero[i][j] == 31){
                texturaActual = esq90g2;
            }
            else if (tablero[i][j] == 32){
                texturaActual = esq90g3;
            }
            else if (tablero[i][j] == 33){
                texturaActual = esq90g4;
            }
            else if (tablero[i][j] == 34){
                texturaActual = borde1;
            }
            else if (tablero[i][j] == 35){
                texturaActual = borde2;
            }
            else if (tablero[i][j] == 36){
                texturaActual = rosado;
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

void animarMuerte(SDL_Renderer* renderer, int **tablero, SDL_Window* initWindow, 
                  SDL_Texture** muerteFrames, int numFrames, int pacmanX, int pacmanY, 
                  SDL_Texture *pillChica, SDL_Texture *superPill, SDL_Texture *esqAbIzq, 
                  SDL_Texture *muroAb, SDL_Texture *muroIzq, SDL_Texture *muroDer, 
                  SDL_Texture *muroArriba, SDL_Texture *esqArribaIzq, SDL_Texture *esqArribaDer, 
                  SDL_Texture *esqAbDer, SDL_Texture *esq1, SDL_Texture *esq2, SDL_Texture *esq3, 
                  SDL_Texture *esq4, SDL_Texture *muroVert1, SDL_Texture *muroVert2, 
                  SDL_Texture *muroHor1, SDL_Texture *muroHor2, SDL_Texture *esq4_2, 
                  SDL_Texture *esq3_2, SDL_Texture *esq1_2, SDL_Texture *esq2_2, 
                  SDL_Texture *interseccion1, SDL_Texture *interseccion2, SDL_Texture *interseccion3, 
                  SDL_Texture *interseccion4, SDL_Texture *interseccion5, SDL_Texture *interseccion6, 
                  SDL_Texture *esq90g1, SDL_Texture *esq90g2, SDL_Texture *esq90g3, SDL_Texture *esq90g4, 
                  SDL_Texture *borde1, SDL_Texture *borde2, SDL_Texture *rosado) {
    int duracionFrame = 2200 / numFrames; // Duración de cada frame en milisegundos

    for (int i = 0; i < numFrames; i++) {
        SDL_RenderClear(renderer);
        // Renderizar el tablero y elementos estáticos
        renderTablero(tablero, initWindow, renderer, pillChica, superPill, esqAbIzq, muroAb, muroIzq, muroDer, 
                      muroArriba, esqArribaIzq, esqArribaDer, esqAbDer, esq1, esq2, esq3, esq4, muroVert1, muroVert2, 
                      muroHor1, muroHor2, esq4_2, esq3_2, esq1_2, esq2_2, interseccion1, interseccion2, 
                      interseccion3, interseccion4, interseccion5, interseccion6, esq90g1, esq90g2, esq90g3, 
                      esq90g4, borde1, borde2, rosado);

        // Renderizar el frame actual de la animación
        SDL_Rect dstRect = {pacmanX, pacmanY, 32, 32}; // Tamaño del sprite de Pac-Man
        SDL_RenderCopy(renderer, muerteFrames[i], NULL, &dstRect);

        SDL_RenderPresent(renderer); // Actualiza la pantalla con el nuevo frame
        SDL_Delay(duracionFrame);    // Espera para mostrar el frame
    }
}

void verificarColisionPacmanFantasma(int *pacmanX, int *pacmanY, 
                                     int *pacmanCasillaX, int *pacmanCasillaY, 
                                     int blinkyX, int blinkyY, 
                                     int pinkyX, int pinkyY, 
                                     int inkyX, int inkyY, 
                                     int clydeX, int clydeY, 
                                     int *vidas, 
                                     SDL_Renderer* renderer, SDL_Texture** muerteFrames, int numFrames,
                                     int **tablero, SDL_Window* initWindow,
                                     SDL_Texture *pillChica, SDL_Texture *superPill, 
                                     SDL_Texture *esqAbIzq, SDL_Texture *muroAb, SDL_Texture *muroIzq, 
                                     SDL_Texture *muroDer, SDL_Texture *muroArriba, SDL_Texture *esqArribaIzq, 
                                     SDL_Texture *esqArribaDer, SDL_Texture *esqAbDer, SDL_Texture *esq1, 
                                     SDL_Texture *esq2, SDL_Texture *esq3, SDL_Texture *esq4, SDL_Texture *muroVert1, 
                                     SDL_Texture *muroVert2, SDL_Texture *muroHor1, SDL_Texture *muroHor2, 
                                     SDL_Texture *esq4_2, SDL_Texture *esq3_2, SDL_Texture *esq1_2, SDL_Texture *esq2_2, 
                                     SDL_Texture *interseccion1, SDL_Texture *interseccion2, SDL_Texture *interseccion3, 
                                     SDL_Texture *interseccion4, SDL_Texture *interseccion5, SDL_Texture *interseccion6, 
                                     SDL_Texture *esq90g1, SDL_Texture *esq90g2, SDL_Texture *esq90g3, SDL_Texture *esq90g4, 
                                     SDL_Texture *borde1, SDL_Texture *borde2, SDL_Texture *rosado,
                                     int *colision){

    // Calcular las casillas de los fantasmas
    int blinkyCasillaX = blinkyX / 16;
    int blinkyCasillaY = blinkyY / 16;
    
    int pinkyCasillaX = pinkyX / 16;
    int pinkyCasillaY = pinkyY / 16;
    
    int inkyCasillaX = inkyX / 16;
    int inkyCasillaY = inkyY / 16;
    
    int clydeCasillaX = clydeX / 16;
    int clydeCasillaY = clydeY / 16;

    // Verificar si Pac-Man y algún fantasma están en la misma casilla
    if ((*pacmanCasillaX == blinkyCasillaX && *pacmanCasillaY == blinkyCasillaY) ||
        (*pacmanCasillaX == pinkyCasillaX && *pacmanCasillaY == pinkyCasillaY) ||
        (*pacmanCasillaX == inkyCasillaX && *pacmanCasillaY == inkyCasillaY) ||
        (*pacmanCasillaX == clydeCasillaX && *pacmanCasillaY == clydeCasillaY)) {
        
        printf("¡Colisión detectada! Pac-Man pierde una vida.\n");

        *vidas -= 1;
        *colision = 1;

        // Reproduce sonido de muerte
        muerte("audio/death_0.wav");
        animarMuerte(renderer, tablero, initWindow, muerteFrames, numFrames, *pacmanX, *pacmanY, 
                     pillChica, superPill, esqAbIzq, muroAb, muroIzq, muroDer, muroArriba, esqArribaIzq, 
                     esqArribaDer, esqAbDer, esq1, esq2, esq3, esq4, muroVert1, muroVert2, muroHor1, 
                     muroHor2, esq4_2, esq3_2, esq1_2, esq2_2, interseccion1, interseccion2, interseccion3, 
                     interseccion4, interseccion5, interseccion6, esq90g1, esq90g2, esq90g3, esq90g4, 
                     borde1, borde2, rosado);

        if (*vidas > 0) {
            // Reiniciar posición del Pac-Man
            *pacmanX = 215; // Coordenada X inicial del sprite
            *pacmanY = 377; // Coordenada Y inicial del sprite
            *pacmanCasillaX = *pacmanX / 16; // Casilla X inicial
            *pacmanCasillaY = *pacmanY / 16; // Casilla Y inicial

            SDL_Delay(2000); // Pausa tras la animación

        } else {
            printf("¡Game Over! Pac-Man no tiene más vidas.\n");
            // Aquí puedes agregar lógica adicional de Game Over si es necesario
        }
    }
}

void destruirTexturas(SDL_Texture *pillChica, SDL_Texture *superPill, SDL_Texture *pacmanReverse, SDL_Texture *esqAbIzq, SDL_Texture *muroAb, SDL_Texture *muroIzq, SDL_Texture *muroDer, SDL_Texture *muroArriba, SDL_Texture *esqArribaIzq, SDL_Texture *esqArribaDer, SDL_Texture *esqAbDer, SDL_Texture *esq1, SDL_Texture *esq2, SDL_Texture *esq3, SDL_Texture *esq4, SDL_Texture *muroVert1, SDL_Texture *muroVert2, SDL_Texture *muroHor1, SDL_Texture *muroHor2, SDL_Texture *esq4_2, SDL_Texture *esq3_2, SDL_Texture *esq1_2, SDL_Texture *esq2_2, SDL_Texture *interseccion1, SDL_Texture *interseccion2, SDL_Texture *interseccion3, SDL_Texture *interseccion4, SDL_Texture *interseccion5, SDL_Texture *interseccion6, SDL_Texture *esq90g1, SDL_Texture *esq90g2, SDL_Texture *esq90g3, SDL_Texture *esq90g4, SDL_Texture *borde1, SDL_Texture *borde2, SDL_Texture *rosado) {

    SDL_DestroyTexture(pillChica);
    SDL_DestroyTexture(superPill);
    SDL_DestroyTexture(pacmanReverse);
    SDL_DestroyTexture(esqAbIzq);
    SDL_DestroyTexture(muroAb);
    SDL_DestroyTexture(muroIzq);
    SDL_DestroyTexture(muroDer);
    SDL_DestroyTexture(muroArriba);
    SDL_DestroyTexture(esqArribaIzq);
    SDL_DestroyTexture(esqArribaDer);
    SDL_DestroyTexture(esqAbDer);
    SDL_DestroyTexture(esq1);
    SDL_DestroyTexture(esq2);
    SDL_DestroyTexture(esq3);
    SDL_DestroyTexture(esq4);
    SDL_DestroyTexture(muroVert1);
    SDL_DestroyTexture(muroVert2);
    SDL_DestroyTexture(muroHor1);
    SDL_DestroyTexture(muroHor2);
    SDL_DestroyTexture(esq4_2);
    SDL_DestroyTexture(esq3_2);
    SDL_DestroyTexture(esq1_2);
    SDL_DestroyTexture(esq2_2);
    SDL_DestroyTexture(interseccion1);
    SDL_DestroyTexture(interseccion2);
    SDL_DestroyTexture(interseccion3);
    SDL_DestroyTexture(interseccion4);
    SDL_DestroyTexture(interseccion5);
    SDL_DestroyTexture(interseccion6);
    SDL_DestroyTexture(esq90g1);
    SDL_DestroyTexture(esq90g2);
    SDL_DestroyTexture(esq90g3);
    SDL_DestroyTexture(esq90g4);
    SDL_DestroyTexture(borde1);
    SDL_DestroyTexture(borde2);
    SDL_DestroyTexture(rosado);
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

    if (!pacmanReverseT) {
        printf("Error al cargar la textura pacmanReverse: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_Rect rectpacmanReverse;
    rectpacmanReverse.w = 24; 
    rectpacmanReverse.h = 24;

    for (int i = 0; i < vidas; i++) {
        rectpacmanReverse.x = 30 + (i * (rectpacmanReverse.w + 5)); 
        rectpacmanReverse.y = 550;

        SDL_RenderCopy(renderer, pacmanReverseT, NULL, &rectpacmanReverse);
    }
}

bool ventanaInicio(SDL_Renderer* renderer, TTF_Font *font) {
    int anchoP = 480;
    int altoP = 580;

    SDL_Event evento;
    bool ejecutando = true;
    SDL_Color colorTexto = {255, 255, 255};
    
    const char* mensajeInicio = "Presione cualquier boton para comenzar";
    
    int contadorParpadeo = 0;
    bool mostrarTexto = true;
    
    SDL_Texture *fondo = cargarTextura(renderer, "img/logoInicio2.png");

    while (ejecutando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                ejecutando = false;
            }
            if (evento.type == SDL_KEYDOWN || evento.type == SDL_MOUSEBUTTONDOWN) {
                //intro("audio/start.wav");
                return true;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro
        SDL_RenderClear(renderer);
        
        if (fondo != NULL) {
            SDL_Rect rectFondo = {15, 70, 226*2, 59*2};  // Usar todo el tamaño de la ventana para el fondo
            SDL_RenderCopy(renderer, fondo, NULL, &rectFondo);
        }

        // Control de parpadeo
        contadorParpadeo++;
        if (contadorParpadeo >= 15) {
            contadorParpadeo = 0;
            mostrarTexto = !mostrarTexto;
        }

        // Si mostrarTexto es true, renderizamos el mensaje
        if (mostrarTexto) {
            SDL_Surface *surface = TTF_RenderText_Solid(font, mensajeInicio, colorTexto);
            if (surface == NULL) {
                printf("Error al crear la superficie de texto: %s\n", TTF_GetError());
                return false;
            }

            SDL_Texture *textura = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            // Obtener el tamaño del texto
            SDL_Rect destRect = { (anchoP - surface->w) / 2, altoP - 40, surface->w, surface->h };

            // Renderizar el texto
            SDL_RenderCopy(renderer, textura, NULL, &destRect);
            SDL_DestroyTexture(textura);
        }

        // Mostrar lo renderizado
        SDL_RenderPresent(renderer);

        // Esperar un poco antes de la siguiente iteración
        SDL_Delay(16); // Controla la velocidad del parpadeo
    }

    SDL_DestroyTexture(fondo);  // Liberar la textura del fondo
    return false; // Si no se presiona nada, se sigue mostrando la ventana de inicio
}

void ventanaJuego(int **tablero) {
    const char *titulo = "Pac-man";
    int anchoP = 480;
    int altoP = 580;
    inicializarSDL();
    Mix_AllocateChannels(32);
    
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

    SDL_Window* ventana = SDL_CreateWindow(titulo, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, anchoP, altoP, SDL_WINDOW_SHOWN);
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

    SDL_Surface *iconSurface = IMG_Load("img/Pacman.png");
    if (iconSurface == NULL) {
        printf("Error al cargar la imagen: %s\n", IMG_GetError());
    }
    // Cargamos todas las texturas para renderizar en el tablero

    SDL_Texture *pillChica = cargarTextura(renderer, "img/pillChica.png");
    SDL_Texture *superPill = cargarTextura(renderer, "img/superpill.png");
    SDL_Texture *pacmanReverse = cargarTextura(renderer, "img/pacmanreveres.png");
    SDL_Texture *esqAbIzq = cargarTextura(renderer, "img/esquinasAbajoIzq.png");
    SDL_Texture *muroAb = cargarTextura(renderer, "img/muroAbajo.png");
    SDL_Texture *muroIzq = cargarTextura(renderer, "img/muroIzq.png");
    SDL_Texture *muroDer = cargarTextura(renderer, "img/muroDerecha.png");
    SDL_Texture *muroArriba = cargarTextura(renderer, "img/muroArriba.png");
    SDL_Texture *esqArribaIzq = cargarTextura(renderer, "img/esquinaArribaIzq.png");
    SDL_Texture *esqArribaDer = cargarTextura(renderer, "img/esquinaArribaDer.png");
    SDL_Texture *esqAbDer = cargarTextura(renderer, "img/esqAbDer.png");
    SDL_Texture *esq1 = cargarTextura(renderer, "img/esq1.png");
    SDL_Texture *esq2 = cargarTextura(renderer, "img/esq2.png");
    SDL_Texture *esq3 = cargarTextura(renderer, "img/esq3.png");
    SDL_Texture *esq4 = cargarTextura(renderer, "img/esq4.png");
    SDL_Texture *muroVert1 = cargarTextura(renderer, "img/muroVert1.png");
    SDL_Texture *muroVert2 = cargarTextura(renderer, "img/muroVert2.png");
    SDL_Texture *muroHor1 = cargarTextura(renderer, "img/muroHor1.png");
    SDL_Texture *muroHor2 = cargarTextura(renderer, "img/muroHor2.png");
    SDL_Texture *esq4_2 = cargarTextura(renderer, "img/esq4_2.png");
    SDL_Texture *esq3_2 = cargarTextura(renderer, "img/esq3_2.png");
    SDL_Texture *esq1_2 = cargarTextura(renderer, "img/esq1_2.png");
    SDL_Texture *esq2_2 = cargarTextura(renderer, "img/esq2_2.png");
    SDL_Texture *interseccion1 = cargarTextura(renderer, "img/interseccion1.png");
    SDL_Texture *interseccion2 = cargarTextura(renderer, "img/interseccion2.png");
    SDL_Texture *interseccion3 = cargarTextura(renderer, "img/interseccion3.png");
    SDL_Texture *interseccion4 = cargarTextura(renderer, "img/interseccion4.png");
    SDL_Texture *interseccion5 = cargarTextura(renderer, "img/interseccion5.png");
    SDL_Texture *interseccion6 = cargarTextura(renderer, "img/interseccion6.png");
    SDL_Texture *esq90g1 = cargarTextura(renderer, "img/esq90g1.png");
    SDL_Texture *esq90g2 = cargarTextura(renderer, "img/esq90g2.png");
    SDL_Texture *esq90g3 = cargarTextura(renderer, "img/esq90g3.png");
    SDL_Texture *esq90g4 = cargarTextura(renderer, "img/esq90g4.png");
    SDL_Texture *borde1 = cargarTextura(renderer, "img/borde1.png");
    SDL_Texture *borde2 = cargarTextura(renderer, "img/borde2.png");
    SDL_Texture *rosado = cargarTextura(renderer, "img/rosado.png");

    //Cargar texturas del pacman
    SDL_Texture* pacmanRight1 = cargarTextura(renderer, "img/pacmanRight1.png");
    SDL_Texture* pacmanRight2 = cargarTextura(renderer, "img/pacmanRight2.png");
    SDL_Texture* pacmanLeft1 = cargarTextura(renderer, "img/pacmanLeft1.png");
    SDL_Texture* pacmanLeft2 = cargarTextura(renderer, "img/pacmanLeft2.png");
    SDL_Texture* pacmanUp1 = cargarTextura(renderer, "img/pacmanUp1.png");
    SDL_Texture* pacmanUp2 = cargarTextura(renderer, "img/pacmanUp2.png");
    SDL_Texture* pacmanDown1 = cargarTextura(renderer, "img/pacmanDown1.png");
    SDL_Texture* pacmanDown2 = cargarTextura(renderer, "img/pacmanDown2.png");

    //Cargar texturas del blinky
    SDL_Texture* blinkyRight1 = cargarTextura(renderer, "img/blinkyRight1.png");
    SDL_Texture* blinkyRight2 = cargarTextura(renderer, "img/blinkyRight2.png");
    SDL_Texture* blinkyLeft1 = cargarTextura(renderer, "img/blinkyLeft1.png");
    SDL_Texture* blinkyLeft2 = cargarTextura(renderer, "img/blinkyLeft2.png");
    SDL_Texture* blinkyUp1 = cargarTextura(renderer, "img/blinkyUp1.png");
    SDL_Texture* blinkyUp2 = cargarTextura(renderer, "img/blinkyUp2.png");
    SDL_Texture* blinkyDown1 = cargarTextura(renderer, "img/blinkyDown1.png");
    SDL_Texture* blinkyDown2 = cargarTextura(renderer, "img/blinkyDown2.png");

    //Cargar texturas del pinky

    SDL_Texture* pinkyRight1 = cargarTextura(renderer, "img/pinkyRight1.png");
    SDL_Texture* pinkyRight2 = cargarTextura(renderer, "img/pinkyRight2.png");
    SDL_Texture* pinkyLeft1 = cargarTextura(renderer, "img/pinkyLeft1.png");
    SDL_Texture* pinkyLeft2 = cargarTextura(renderer, "img/pinkyLeft2.png");
    SDL_Texture* pinkyUp1 = cargarTextura(renderer, "img/pinkyUp1.png");
    SDL_Texture* pinkyUp2 = cargarTextura(renderer, "img/pinkyUp2.png");
    SDL_Texture* pinkyDown1 = cargarTextura(renderer, "img/pinkyDown1.png");
    SDL_Texture* pinkyDown2 = cargarTextura(renderer, "img/pinkyDown2.png");

    //cargar texturas del inky

    SDL_Texture* inkyRight1 = cargarTextura(renderer, "img/inkyRight1.png");
    SDL_Texture* inkyRight2 = cargarTextura(renderer, "img/inkyRight2.png");
    SDL_Texture* inkyLeft1 = cargarTextura(renderer, "img/inkyLeft1.png");
    SDL_Texture* inkyLeft2 = cargarTextura(renderer, "img/inkyLeft2.png");
    SDL_Texture* inkyUp1 = cargarTextura(renderer, "img/inkyUp1.png");
    SDL_Texture* inkyUp2 = cargarTextura(renderer, "img/inkyUp2.png");
    SDL_Texture* inkyDown1 = cargarTextura(renderer, "img/inkyDown1.png");
    SDL_Texture* inkyDown2 = cargarTextura(renderer, "img/inkyDown2.png");

    //cargar texturas del clyde
    SDL_Texture* clydeRight1 = cargarTextura(renderer, "img/clydeRight1.png");
    SDL_Texture* clydeRight2 = cargarTextura(renderer, "img/clydeRight2.png");
    SDL_Texture* clydeLeft1 = cargarTextura(renderer, "img/clydeLeft1.png");
    SDL_Texture* clydeLeft2 = cargarTextura(renderer, "img/clydeLeft2.png");
    SDL_Texture* clydeUp1 = cargarTextura(renderer, "img/clydeUp1.png");
    SDL_Texture* clydeUp2 = cargarTextura(renderer, "img/clydeUp2.png");
    SDL_Texture* clydeDown1 = cargarTextura(renderer, "img/clydeDown1.png");
    SDL_Texture* clydeDown2 = cargarTextura(renderer, "img/clydeDown2.png");
    
    //Texturas de muerte

    SDL_Texture* muerteFrames[10];
    muerteFrames[0] = cargarTextura(renderer, "img/death1.png");
    muerteFrames[1] = cargarTextura(renderer, "img/death2.png");
    muerteFrames[2] = cargarTextura(renderer, "img/death3.png");
    muerteFrames[3] = cargarTextura(renderer, "img/death4.png");
    muerteFrames[4] = cargarTextura(renderer, "img/death5.png");
    muerteFrames[5] = cargarTextura(renderer, "img/death6.png");
    muerteFrames[6] = cargarTextura(renderer, "img/death7.png");
    muerteFrames[7] = cargarTextura(renderer, "img/death8.png");
    muerteFrames[8] = cargarTextura(renderer, "img/death9.png");
    muerteFrames[9] = cargarTextura(renderer, "img/death10.png");
    muerteFrames[10] = cargarTextura(renderer, "img/death11.png");


    TTF_Font *font = TTF_OpenFont("font/ARCADECLASSIC.ttf", 24);
    if (font == NULL) {
        printf("No se pudo cargar la fuente: %s\n", TTF_GetError());
        return;
    }

    // Bucle principal

    int HIGH_SCORE = 0;
    int ejecutando = 1;
    int vidas = 4;
    //int de la función tablero para poder calcular bien dónde
    //va a estar el pacman en relación a la matriz original
    int f = tamanoFilas(tablero);
    int c = tamanoColumnas(tablero);
    int anchoCelda = 448 / c;
    int altoCelda = 496 / f;
    int colision = 0;
    int invul = 1;
    int pill_time = 0;
    int colision_time = 0;

    //PARA EL PACMAN
    //---------------------------------------------
    //coordenadas de inicio en terminos de matriz
    int coor_x = 13;
    int coor_y = 23;
    
    //coordenadas de inicio en terminos de ventana
    int inicial_x = 215;
    int inicial_y = 377;
    
    int estado = 0;
    int dir_actual = RIGHT;
    Uint32 lastTime = 0;
    Uint32 last_move_time = SDL_GetTicks();

    //---------------------------------------------

    int blinkyX = 215;
    int blinkyY = 182;
    int direccionBlinky=0; // Dirección inicial de Blinky
    int blinkyEstado = 0;    // Estado inicial de Blinky

    //---------------------------------------------

    int pinkyX = 215;
    int pinkyY = 182;
    int direccionpinky=0; // Dirección inicial de Pinky
    int pinkyEstado = 0;    // Estado inicial de Pinky

    //---------------------------------------------

    int inkyX = 215;
    int inkyY = 182;
    int direccioninky=0; // Dirección inicial de inky
    int inkyEstado = 0;    // Estado inicial de inky

    //---------------------------------------------

    int clydeX = 215;
    int clydeY = 182;
    int direccionclyde=0; // Dirección inicial de clyde
    int clydeEstado = 0;    // Estado inicial de clyde


    Uint32 ticks = SDL_GetTicks();

    SDL_SetWindowIcon(ventana, iconSurface);

    if (!ventanaInicio(renderer, font)) {
        // Si no se presiona ninguna tecla o botón, salimos del juego
        SDL_Quit();
        return;
    }

    SDL_Event evento;
    //esta constante es la base de la deteccion de teclas
    const Uint8* key = SDL_GetKeyboardState(NULL);

    srand(time(NULL));

    direccionBlinky = rand()%4;

    while (ejecutando) {

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Renderizar el tablero y la interfaz
        renderTablero(tablero, ventana, renderer, pillChica, superPill, esqAbIzq, muroAb, muroIzq, muroDer, muroArriba, esqArribaIzq, esqArribaDer, esqAbDer,   esq1, esq2, esq3, esq4, muroVert1, muroVert2, muroHor1, muroHor2, esq4_2, esq3_2, esq1_2, esq2_2, interseccion1, interseccion2, interseccion3,    interseccion4, interseccion5, interseccion6, esq90g1, esq90g2, esq90g3, esq90g4, borde1, borde2, rosado);
        
        imagenVidas(ventana, renderer, pacmanReverse, vidas);

        char texto[50];
        snprintf(texto, sizeof(texto), "%d", HIGH_SCORE);
        renderText(renderer, font, "1 UP", 300 - 16*6, 520);
        renderText(renderer, font, "HIGH SCORE", 350, 520);
        renderText(renderer, font, texto, 350 + 32 +12, 540);
        renderText(renderer, font, texto, 300 - 16*6, 540);

        sirena("audio/siren0_firstloop.wav");
        
        //teletransportar en los bordes
        if(coor_x == 0){
            coor_x = 26;
            inicial_x = 215 + anchoCelda*13;
        }
        if(coor_x == 27){
            coor_x = 1;
            inicial_x = 215 - anchoCelda*12;
        }

        // Manejar eventos
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                ejecutando = 0;
            } else if (evento.type == SDL_KEYDOWN) {
                if (key[SDL_SCANCODE_UP] && checking(tablero, coor_x, coor_y - 1, &HIGH_SCORE, &pill_time)) {
                    dir_actual = UP;
                }
                if (key[SDL_SCANCODE_DOWN] && checking(tablero, coor_x, coor_y + 1, &HIGH_SCORE, &pill_time)) {
                    dir_actual = DOWN;
                }
                if (key[SDL_SCANCODE_LEFT] && checking(tablero, coor_x - 1, coor_y, &HIGH_SCORE, &pill_time)) {
                    dir_actual = LEFT;
                }
                if (key[SDL_SCANCODE_RIGHT] && checking(tablero, coor_x + 1, coor_y, &HIGH_SCORE, &pill_time)) {
                    dir_actual = RIGHT;
                }
            }
        }

        Uint32 current_time = SDL_GetTicks(); // Tiempo actual
        if (current_time >= last_move_time + pacmanSpeed+10) { // Controlar el tiempo entre movimientos
            switch (dir_actual) {
                case UP:
                    if (checking(tablero, coor_x, coor_y - 1, &HIGH_SCORE, &pill_time)) {
                        inicial_y -= altoCelda;
                        coor_y--;
                    }
                    break;
                case DOWN:
                    if (checking(tablero, coor_x, coor_y + 1, &HIGH_SCORE, &pill_time)) {
                        inicial_y += altoCelda;
                        coor_y++;
                    }
                    break;
                case LEFT:
                    if (checking(tablero, coor_x - 1, coor_y, &HIGH_SCORE, &pill_time)) {
                        inicial_x -= anchoCelda;
                        coor_x--;
                    }
                    break;
                case RIGHT:
                    if (checking(tablero, coor_x + 1, coor_y, &HIGH_SCORE, &pill_time)) {
                        inicial_x += anchoCelda;
                        coor_x++;
                    }
                    break;
                default:
                    break; // No hay movimiento
            }
            last_move_time = current_time; // Actualizar el tiempo del último movimiento
        }

        // Dibujar Pac-Man en su posición actual
        pacman(inicial_x, inicial_y, renderer, pacmanRight1, pacmanRight2, pacmanLeft1, pacmanLeft2, pacmanUp1, pacmanUp2, pacmanDown1, pacmanDown2, &estado, dir_actual, &lastTime, invul);

        //blinky
        moverFantasma(renderer, blinkyRight1, blinkyRight2, blinkyLeft1, blinkyLeft2, 
                  blinkyUp1, blinkyUp2, blinkyDown1, blinkyDown2, 
                  &blinkyX, &blinkyY, &direccionBlinky, &blinkyEstado, 
                  &ticks, &coor_x, &coor_y, tablero, anchoP, altoP);

        //pinky
        if(current_time > 5000){
            moverFantasma(renderer, pinkyRight1, pinkyRight2, pinkyLeft1, pinkyLeft2, 
                  pinkyUp1, pinkyUp2, pinkyDown1, pinkyDown2, 
                  &pinkyX, &pinkyY, &direccionpinky, &pinkyEstado, 
                  &ticks, &coor_x, &coor_y, tablero, anchoP, altoP);
        }
        else{
            SDL_Rect dstRect = {245, 230, 32, 32};
            SDL_RenderCopy(renderer, pinkyRight1, NULL, &dstRect);
            SDL_RenderCopy(renderer, pinkyRight2, NULL, &dstRect);
        }

        //inky
        if(current_time > 10000){
            moverFantasma(renderer, inkyRight1, inkyRight2, inkyLeft1, inkyLeft2, 
                  inkyUp1, inkyUp2, inkyDown1, inkyDown2, 
                  &inkyX, &inkyY, &direccioninky, &inkyEstado, 
                  &ticks, &coor_x, &coor_y, tablero, anchoP, altoP);
        }
        else{
            SDL_Rect dstRect = {224, 230, 32, 32};
            SDL_RenderCopy(renderer, inkyRight1, NULL, &dstRect);
            SDL_RenderCopy(renderer, inkyRight2, NULL, &dstRect);
        }

        //clyde
        if(current_time > 15000){
            moverFantasma(renderer, clydeRight1, clydeRight2, clydeLeft1, clydeLeft2, 
                  clydeUp1, clydeUp2, clydeDown1, clydeDown2, 
                  &clydeX, &clydeY, &direccionclyde, &clydeEstado, 
                  &ticks, &coor_x, &coor_y, tablero, anchoP, altoP);
        }
        else{
            SDL_Rect dstRect = {200, 230, 32, 32};
            SDL_RenderCopy(renderer, clydeRight1, NULL, &dstRect);
            SDL_RenderCopy(renderer, clydeRight2, NULL, &dstRect);
        }

        //tiempo de gracia después de cada colisión contra fantasmas
        if(current_time - colision_time > 7000){ 
            invul = 0;
        // si pasan 7 seg después de la ultima colisión se activa la detección otra vez
            verificarColisionPacmanFantasma(&inicial_x, &inicial_y, &coor_x, &coor_y,
                                blinkyX, blinkyY, pinkyX, pinkyY,
                                inkyX, inkyY, clydeX, clydeY,
                                &vidas, renderer, muerteFrames, 10,
                                tablero, ventana,
                                pillChica, superPill, esqAbIzq, muroAb, muroIzq, muroDer,
                                muroArriba, esqArribaIzq, esqArribaDer, esqAbDer, esq1,
                                esq2, esq3, esq4, muroVert1, muroVert2, muroHor1,
                                muroHor2, esq4_2, esq3_2, esq1_2, esq2_2, interseccion1,
                                interseccion2, interseccion3, interseccion4, interseccion5,
                                interseccion6, esq90g1, esq90g2, esq90g3, esq90g4, borde1,
                                borde2, rosado, &colision);
            if(colision == 1){
                colision_time = current_time;
                colision = 0;
                invul = 1;
            }
        }
        
        if (vidas==0){
            printf("Game over!");
            ejecutando=0;
        
        }
        if (HIGH_SCORE == 2600){
            printf("Has ganado!");
            ejecutando=0;
        }
        
        // Renderizar en pantalla
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    for (int i=0; i<11; i++){
        SDL_DestroyTexture(muerteFrames[i]);
    }

    destruirTexturas(pillChica, superPill, pacmanReverse, esqAbIzq, muroAb, muroIzq, muroDer, muroArriba, esqArribaIzq, esqArribaDer, esqAbDer, esq1, esq2, esq3, esq4, muroVert1, muroVert2, muroHor1, muroHor2, esq4_2, esq3_2, esq1_2, esq2_2, interseccion1, interseccion2, interseccion3, interseccion4, interseccion5, interseccion6, esq90g1, esq90g2, esq90g3, esq90g4, borde1, borde2, rosado);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    SDL_FreeSurface(iconSurface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}