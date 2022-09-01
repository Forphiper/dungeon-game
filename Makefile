CC = g++
COMPILER_FLAGS = -Wall -g `sdl2-config --cflags`
INCLUDES = -I /usr/include/SDL2
RM = rm -f
LINKER_FLAGS = `sdl2-config --libs` -L /usr/lib/x86_64-linux-gnu -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJECTS = Animal.o Narwhal.o

all: ${OBJECTS}
	${CC} ${COMPILER_FLAGS} ${INCLUDES} main.cpp ${OBJECTS} ${LINKER_FLAGS} -o main

Animal.o:Animal.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} Animal.cpp -c -o Animal.o

Narwhal.o:Narwhal.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} Narwhal.cpp -c -o Narwhal.o


clean:
	${RM} main
	${RM} ${OBJECTS}