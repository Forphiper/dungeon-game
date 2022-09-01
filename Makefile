CC = g++
COMPILER_FLAGS = -Wall -g `sdl2-config --cflags`
INCLUDES = -I /usr/include/SDL2
RM = rm -f
LINKER_FLAGS = `sdl2-config --libs` -L /usr/lib/x86_64-linux-gnu -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJECTS = Character.o Hero.o Glob.o MapScreen.o MapObject.o

all: ${OBJECTS}
	${CC} ${COMPILER_FLAGS} ${INCLUDES} main.cpp ${OBJECTS} ${LINKER_FLAGS} -o main

Character.o:Character.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} Character.cpp -c -o Character.o

Hero.o:Hero.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} Hero.cpp -c -o Hero.o

Glob.o:Glob.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} Glob.cpp -c -o Glob.o

MapScreen.o:MapScreen.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} MapScreen.cpp -c -o MapScreen.o

MapObject.o:MapObject.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} MapObject.cpp -c -o MapObject.o

clean:
	${RM} main
	${RM} ${OBJECTS}