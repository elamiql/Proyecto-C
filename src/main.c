#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }
    // Crear una ventana
    SDL_Window* ventana = SDL_CreateWindow(
        "Pac-Man",                // Título de la ventana
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
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Error al inicializar SDL_image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = IMG_Load("img/pacman.jpg");
    if (!surface) {
        printf("Error al cargar la imagen: %s\n", IMG_GetError());
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("Error al crear la textura: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(ventana);
        SDL_Quit();
        return 1;
    }
    //AGREGAR AUDIO
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("No se pudo inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }

    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
        printf("No se pudo inicializar SDL_mixer: %s\n", Mix_GetError());
        return -1;
    }
    
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("No se pudo abrir el audio: %s\n", Mix_GetError());
        return -1;
    }

    Mix_Music *music = Mix_LoadMUS("audio/intro.mp3");
    if (!music) {
        printf("No se pudo cargar la música: %s\n", Mix_GetError());
        return -1;
    }

    Mix_PlayMusic(music, -1); // -1 para reproducción en loop infinito
    Mix_VolumeMusic(1);



    // Bucle para mantener la ventana abierta
    int ejecutando = 1;
    SDL_Event evento;
    while (ejecutando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                ejecutando = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Limpiar y cerrar SDL
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    return 0;
}

