CC = g++
COMPILER_FLAGS = -Wall -g `sdl2-config --cflags`
INCLUDES = -I /usr/include/SDL2
RM = rm -f
LINKER_FLAGS = `sdl2-config --libs` -L /usr/lib/x86_64-linux-gnu -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJECTS = Character.o Hero.o Glob.o Mimic.o MapScreen.o MapObject.o InfoBox.o BattleScreen.o Animation.o AnimationManager.o CharacterAnimationSet.o

all: ${OBJECTS}
	${CC} ${COMPILER_FLAGS} ${INCLUDES} main.cpp ${OBJECTS} ${LINKER_FLAGS} -o main

Character.o:Character.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} Character.cpp -c -o Character.o

Hero.o:Hero.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} Hero.cpp -c -o Hero.o

Glob.o:Glob.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} Glob.cpp -c -o Glob.o

Mimic.o:Mimic.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} Mimic.cpp -c -o Mimic.o

MapScreen.o:MapScreen.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} MapScreen.cpp -c -o MapScreen.o

MapObject.o:MapObject.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} MapObject.cpp -c -o MapObject.o

InfoBox.o:InfoBox.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} InfoBox.cpp -c -o InfoBox.o

BattleScreen.o:BattleScreen.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} BattleScreen.cpp -c -o BattleScreen.o

Animation.o:Animation.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} Animation.cpp -c -o Animation.o

AnimationManager.o:AnimationManager.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} AnimationManager.cpp -c -o AnimationManager.o

CharacterAnimationSet.o:CharacterAnimationSet.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} CharacterAnimationSet.cpp -c -o CharacterAnimationSet.o

clean:
	${RM} main
	${RM} ${OBJECTS}