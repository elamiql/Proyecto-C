#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

void intro(const char *archivo_audio) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return;
    }

    // Inicializar SDL_mixer
    if (Mix_Init(MIX_INIT_MP3) == 0) {
        printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
        SDL_Quit();
        return;
    }

    // Abrir el mezclador de audio con parámetros predeterminados
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Error al abrir el audio: %s\n", Mix_GetError());
        Mix_Quit();
        SDL_Quit();
        return;
    }

    // Cargar el archivo de música
    Mix_Music *musica = Mix_LoadMUS(archivo_audio);
    if (musica == NULL) {
        printf("Error al cargar la música: %s\n", Mix_GetError());
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        return;
    }

    // Reproducir la música una vez
    if (Mix_PlayMusic(musica, 1) == -1) {
        printf("Error al reproducir música: %s\n", Mix_GetError());
        Mix_FreeMusic(musica);
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        return;
    }
}