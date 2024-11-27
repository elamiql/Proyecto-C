#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int inicializarSDL();
void intro(const char *archivo_audio);
void chomp(const char *archivo_audio1, const char *archivo_audio2);
void sirena(const char *archivo);
void muerte(const char *archivo);

#endif