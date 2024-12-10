#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

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

int checking(int **tablero, int x, int y, int *HIGH_SCORE, int *pill_time){
    if(tablero[y][x] == 3 ){
        tablero[y][x] = 0;
        *HIGH_SCORE += 50;
        *pill_time = 1;
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

int checkingFantasmas(int **tablero, int x, int y){
    if(tablero[y][x] == 3 ){
        return 1;
    }
    else if(tablero[y][x] == 0){
        return 1;
    }
    else if(tablero[y][x] == 2){
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
            int* estado, int direccion, Uint32* lastTime, int colision) {
    
    SDL_Rect pacmanRect = {x1, y1, 32, 32};  // Ajusta las dimensiones de Pac-Man
    SDL_Texture* currentTexture = NULL;
    Uint32 currentTime = SDL_GetTicks();  // Obtiene el tiempo actual en milisegundos
    
    // Cambiar el estado solo si ha pasado suficiente tiempo
    if (currentTime - *lastTime > 80) {  // 100 ms de intervalo
        *estado = 1 - *estado;  // Cambiar entre 0 y 1
        *lastTime = currentTime;  // Actualizar el último tiempo
    }

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

    if(colision == 1){
        if(currentTime%550 > 375){
            currentTexture = NULL;
        }
    }
    // Renderizar el sprite actual
    SDL_RenderCopy(renderer, currentTexture, NULL, &pacmanRect);
}

void moverFantasma(SDL_Renderer *renderer, SDL_Texture* FantasmaRight1, SDL_Texture* FantasmaRight2, 
                   SDL_Texture* FantasmaLeft1, SDL_Texture* FantasmaLeft2, 
                   SDL_Texture* FantasmaUp1, SDL_Texture* FantasmaUp2, 
                   SDL_Texture* FantasmaDown1, SDL_Texture* FantasmaDown2, 
                   int *FantasmaX, int *FantasmaY, int *direccionFantasma, int *FantasmaEstado, 
                   Uint32 *ticks, int *coorX, int *coorY, int **tablero, int anchoP, int altoP) {

    int velocidad = 16; // Velocidad de Fantasma (16 píxeles por movimiento)
    SDL_Texture *FantasmaTexture = NULL;
    
    // Cambiar dirección aleatoria cada cierto tiempo (aumentar el tiempo para hacerlo más lento)
    if (SDL_GetTicks() - *ticks > 600) { // Aumentar el tiempo de cambio de dirección (1 segundo)
        *direccionFantasma = rand() % 4; // Direcciones aleatorias (0: ARRIBA, 1: ABAJO, 2: IZQUIERDA, 3: DERECHA)
        *ticks = SDL_GetTicks(); // Reiniciar el contador de tiempo
    }
        // Intentar mover Fantasma según su dirección
    int nuevaX = *FantasmaX, nuevaY = *FantasmaY;
    switch (*direccionFantasma) {
        case 0: // Arriba
            nuevaY -= velocidad;
            FantasmaTexture = (*FantasmaEstado % 2 == 0) ? FantasmaUp1 : FantasmaUp2;
            break;
        case 1: // Abajo
            nuevaY += velocidad;
            FantasmaTexture = (*FantasmaEstado % 2 == 0) ? FantasmaDown1 : FantasmaDown2;
            break;
        case 2: // Izquierda
            nuevaX -= velocidad;
            FantasmaTexture = (*FantasmaEstado % 2 == 0) ? FantasmaLeft1 : FantasmaLeft2;
            break;
        case 3: // Derecha
            nuevaX += velocidad;
            FantasmaTexture = (*FantasmaEstado % 2 == 0) ? FantasmaRight1 : FantasmaRight2;
            break;
    }

    // Verificar si la nueva posición está dentro de los límites del mapa y la ventana
    if (checkingFantasmas(tablero, nuevaX / 16, nuevaY / 16)) { // Asumiendo que cada celda es de 16x16
        // Asegurarse de que Fantasma no se salga de los bordes de la ventana
        if (nuevaX >= 0 && nuevaX <= anchoP - 32 && nuevaY >= 0 && nuevaY <= altoP - 32) {
            *FantasmaX = nuevaX;
            *FantasmaY = nuevaY;
        }
    }

    // Alternar entre las texturas de Fantasma (animación)
    *FantasmaEstado = (*FantasmaEstado + 1) % 2;
    
    // Dibujar Fantasma en su nueva posición (renderizar a 32x32)
    SDL_Delay(6); // Retraso mayor para ralentizar el movimiento
    SDL_Rect dstRect = {*FantasmaX, *FantasmaY, 32, 32}; // Renderizar el sprite como 32x32
    SDL_RenderCopy(renderer, FantasmaTexture, NULL, &dstRect);
}
