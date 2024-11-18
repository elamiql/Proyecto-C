CC = gcc
CFLAGS = -Wall -g -IC:\SDL2\include
LDFLAGS = -LC:\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

SRC = src/main.c src/audio.c src/funciones.c src/ventana.c
OBJ = $(SRC:.c=.o)
EXEC = pacman

# Regla por defecto
all: $(EXEC)

# Compilación de los archivos fuente
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Compilación de los archivos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJ) $(EXEC)