#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Crear una ventana
    SDL_Window* ventana = SDL_CreateWindow(
        "Mi ventana SDL2",                // Título de la ventana
        SDL_WINDOWPOS_CENTERED,           // Posición X
        SDL_WINDOWPOS_CENTERED,           // Posición Y
        800,                              // Ancho de la ventana
        600,                              // Alto de la ventana
        SDL_WINDOW_SHOWN                  // Bandera para mostrar la ventana
    );

    if (!ventana) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Crear un renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    // Bucle para mantener la ventana abierta
    int ejecutando = 1;
    SDL_Event evento;
    while (ejecutando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                ejecutando = 0;
            }
        }

        // Establecer color de renderizado (blanco)
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

        // Limpiar la pantalla con el color establecido
        SDL_RenderClear(renderer);

        // Presentar el renderizador en pantalla
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Pequeño retraso para evitar uso excesivo de CPU
    }

    // Limpiar y cerrar SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return 0;
}

