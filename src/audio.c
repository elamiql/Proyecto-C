#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

int alternador_sonido = 0;

// Función para cargar los sonidos
Mix_Chunk* cargarSonido(const char *archivo_audio) {
    Mix_Chunk *sonido = Mix_LoadWAV(archivo_audio);
    if (sonido == NULL) {
        printf("Error al cargar el sonido %s: %s\n", archivo_audio, Mix_GetError());
    }
    return sonido;
}

int inicializarSDL() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return 0;
    }

    if (Mix_Init(MIX_INIT_MP3) == 0) {
        printf("Error al inicializar SDL_mixer: %s\n", Mix_GetError());
        SDL_Quit();
        return 0;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Error al abrir el audio: %s\n", Mix_GetError());
        Mix_Quit();
        SDL_Quit();
        return 0;
    }

    return 1;
}

void intro(const char *archivo_audio) {
    Mix_Music *musica = Mix_LoadMUS(archivo_audio);
    if (musica == NULL) {
        printf("Error al cargar la música: %s\n", Mix_GetError());
        return;
    }

    if (Mix_PlayMusic(musica, 1) == -1) {
        printf("Error al reproducir música: %s\n", Mix_GetError());
        Mix_FreeMusic(musica);
    }
}

// Función para reproducir los sonidos alternados
void chomp(const char *archivo_audio1, const char *archivo_audio2) {
    static Mix_Chunk *sonido1 = NULL;
    static Mix_Chunk *sonido2 = NULL;

    // Inicializar SDL_mixer si es la primera vez
    static int inicializado = 0;
    if (!inicializado) {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("Error al abrir el audio: %s\n", Mix_GetError());
            return;
        }
        sonido1 = cargarSonido(archivo_audio1);
        sonido2 = cargarSonido(archivo_audio2);
        inicializado = 1;
    }

    // Seleccionar el sonido basado en el alternador
    Mix_Chunk *sonido_actual = (alternador_sonido == 0) ? sonido1 : sonido2;

    if (sonido_actual) {
        if (Mix_PlayChannel(2, sonido_actual, 0) == -1) {
            printf("Error al reproducir el sonido: %s\n", Mix_GetError());
        }
    } else {
        printf("No se pudieron cargar los sonidos correctamente.\n");
    }
    Mix_VolumeChunk(sonido_actual, 15);
    // Alternar el sonido
    alternador_sonido = 1 - alternador_sonido;
}

void sirena(const char *archivo) {
    static Mix_Chunk *sonido_sirena = NULL;
    
    // Si el sonido no está cargado, cargarlo
    if (!sonido_sirena) {
        sonido_sirena = cargarSonido(archivo);
        if (!sonido_sirena) {
            printf("Error al cargar el sonido de la sirena: %s\n", Mix_GetError());
            return;
        }
    }

    // Comprobar si ya se está reproduciendo la sirena
    if (!Mix_Playing(0)) {  // Canal 0 reservado para la sirena
        // Reproducir la sirena en canal 0 (en bucle)
        if (Mix_PlayChannel(0, sonido_sirena, -1) == -1) {
            printf("Error al reproducir la sirena: %s\n", Mix_GetError());
        }
    }
    Mix_VolumeChunk(sonido_sirena, 15);
}