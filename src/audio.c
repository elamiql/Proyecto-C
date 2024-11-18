#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

int intro(){

    //Funciones para tomar errores

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }
 
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
        return -1;
    }

    Mix_Music *music = Mix_LoadMUS("audio/intro.mp3");
    if (music == NULL) {
        printf("Error al cargar música: %s\n", Mix_GetError());
    return -1;
}
    if (!music) {
        printf("Error al cargar archivos de audio: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    // Reproducir música
    Mix_PlayMusic(music, -1);

    // Aumentar el volumen de la música al 75%
    Mix_VolumeMusic(96);

    // Establecer el volumen de los efectos de sonido al 50%
    Mix_Volume(-1, 64);

    // Esperar para que el sonido se reproduzca
    SDL_Delay(5000);

    // Limpiar y cerrar
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

}