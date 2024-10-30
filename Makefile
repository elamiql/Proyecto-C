all:
	gcc -o pacman src/main.c -IC:\SDL2\include -LC:\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
