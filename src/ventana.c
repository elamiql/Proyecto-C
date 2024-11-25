#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "audio.h"
#include "funciones.h"

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

#define pacmanSpeed 150


const int offsetY = 48;
const int offsetX = 16;

SDL_Texture* cargarTextura(SDL_Renderer* renderer, const char* ruta) {
    SDL_Texture* textura = IMG_LoadTexture(renderer, ruta);
    if (!textura) {
        printf("Error al cargar la textura %s: %s\n", ruta, IMG_GetError());
    }
    return textura;
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
    SDL_Texture* pacmanRight1 = cargarTextura(renderer, "img/pacmanRight1.png");
    SDL_Texture* pacmanRight2 = cargarTextura(renderer, "img/pacmanRight2.png");
    SDL_Texture* pacmanLeft1 = cargarTextura(renderer, "img/pacmanLeft1.png");
    SDL_Texture* pacmanLeft2 = cargarTextura(renderer, "img/pacmanLeft2.png");
    SDL_Texture* pacmanUp1 = cargarTextura(renderer, "img/pacmanUp1.png");
    SDL_Texture* pacmanUp2 = cargarTextura(renderer, "img/pacmanUp2.png");
    SDL_Texture* pacmanDown1 = cargarTextura(renderer, "img/pacmanDown1.png");
    SDL_Texture* pacmanDown2 = cargarTextura(renderer, "img/pacmanDown2.png");

    //SDL_Texture *Blinky = cargarTextura(renderer, "img/Blinky.png");


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

    //PARA EL PACMAN
    //---------------------------------------------
    //coordenadas de inicio en terminos de matriz
    int coor_x = 13;
    int coor_y = 23;
    
    //coordenadas de inicio en terminos de ventana
    int inicial_x = 215;
    int inicial_y = 409;
    
    int estado = 0;
    int dir_actual = RIGHT;

    //---------------------------------------------

    Uint32 last_move_time = 0;
    
    SDL_SetWindowIcon(ventana, iconSurface);

    if (!ventanaInicio(renderer, font)) {
        // Si no se presiona ninguna tecla o botón, salimos del juego
        SDL_Quit();
        return;
    }

    SDL_Event evento;
    //esta constante es la base de la deteccion de teclas
    const Uint8* key = SDL_GetKeyboardState(NULL);
    
    while (ejecutando) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Renderizar el tablero y la interfaz
        renderTablero(tablero, ventana, renderer, pillChica, superPill, esqAbIzq, muroAb, muroIzq, muroDer, muroArriba, esqArribaIzq, esqArribaDer, esqAbDer,   esq1, esq2, esq3, esq4, muroVert1, muroVert2, muroHor1, muroHor2, esq4_2, esq3_2, esq1_2, esq2_2, interseccion1, interseccion2, interseccion3,    interseccion4, interseccion5, interseccion6, esq90g1, esq90g2, esq90g3, esq90g4, borde1, borde2, rosado);
        imagenVidas(ventana, renderer, pacmanReverse, vidas);

        char texto[50];
        snprintf(texto, sizeof(texto), "%d", HIGH_SCORE);
        renderText(renderer, font, "1 UP", 20, 0);
        renderText(renderer, font, "HIGH SCORE", (anchoP - 110) / 2, 0);
        renderText(renderer, font, texto, (anchoP - 30) / 2, 20);
        renderText(renderer, font, texto, (30), 20);

        sirena("audio/siren0_firstloop.wav");
        
        // Manejar eventos
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                ejecutando = 0;
            } else if (evento.type == SDL_KEYDOWN) {
                if (key[SDL_SCANCODE_UP] && checking(tablero, coor_x, coor_y - 1, &HIGH_SCORE)) {
                    dir_actual = UP;
                }
                if (key[SDL_SCANCODE_DOWN] && checking(tablero, coor_x, coor_y + 1, &HIGH_SCORE)) {
                    dir_actual = DOWN;
                }
                if (key[SDL_SCANCODE_LEFT] && checking(tablero, coor_x - 1, coor_y, &HIGH_SCORE)) {
                    dir_actual = LEFT;
                }
                if (key[SDL_SCANCODE_RIGHT] && checking(tablero, coor_x + 1, coor_y, &HIGH_SCORE)) {
                    dir_actual = RIGHT;
                }
            }
        }

        Uint32 current_time = SDL_GetTicks(); // Tiempo actual
        if (current_time > last_move_time + pacmanSpeed) { // Controlar el tiempo entre movimientos
            switch (dir_actual) {
                case UP:
                    if (checking(tablero, coor_x, coor_y - 1, &HIGH_SCORE)) {
                        inicial_y -= altoCelda;
                        coor_y--;
                    }
                    break;
                case DOWN:
                    if (checking(tablero, coor_x, coor_y + 1, &HIGH_SCORE)) {
                        inicial_y += altoCelda;
                        coor_y++;
                    }
                    break;
                case LEFT:
                    if (checking(tablero, coor_x - 1, coor_y, &HIGH_SCORE)) {
                        inicial_x -= anchoCelda;
                        coor_x--;
                    }
                    break;
                case RIGHT:
                    if (checking(tablero, coor_x + 1, coor_y, &HIGH_SCORE)) {
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
        pacman(inicial_x, inicial_y, renderer, pacmanRight1, pacmanRight2, pacmanLeft1, pacmanLeft2, pacmanUp1, pacmanUp2, pacmanDown1, pacmanDown2, &estado, dir_actual);

        // Renderizar en pantalla
        SDL_RenderPresent(renderer);
        SDL_Delay(90);
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