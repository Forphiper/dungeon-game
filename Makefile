CC = g++
COMPILER_FLAGS = -Wall -g `sdl2-config --cflags`
INCLUDES = -I /usr/include/SDL2 -I ./include
RM = rm -f
LINKER_FLAGS = `sdl2-config --libs` -L /usr/lib/x86_64-linux-gnu -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJECTS = ./build/Character.o ./build/Hero.o ./build/Glob.o ./build/Mimic.o ./build/MapScreen.o ./build/MapObject.o \
./build/InfoBox.o ./build/BattleScreen.o ./build/Animation.o ./build/AnimationManager.o \
./build/CharacterAnimationSet.o ./build/HPBar.o ./build/BattleButton.o ./build/BattleEffects.o \
./build/ItemMenu.o

all: ${OBJECTS}
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/main.cpp ${OBJECTS} ${LINKER_FLAGS} -o ./bin/main

./build/Character.o:./src/Character.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/Character.cpp -c -o ./build/Character.o

./build/Hero.o:./src/Hero.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/Hero.cpp -c -o ./build/Hero.o

./build/Glob.o:./src/Glob.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/Glob.cpp -c -o ./build/Glob.o

./build/Mimic.o:./src/Mimic.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/Mimic.cpp -c -o ./build/Mimic.o

./build/MapScreen.o:./src/MapScreen.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/MapScreen.cpp -c -o ./build/MapScreen.o

./build/MapObject.o:./src/MapObject.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/MapObject.cpp -c -o ./build/MapObject.o

./build/InfoBox.o:./src/InfoBox.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/InfoBox.cpp -c -o ./build/InfoBox.o

./build/BattleScreen.o:./src/BattleScreen.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/BattleScreen.cpp -c -o ./build/BattleScreen.o

./build/Animation.o:./src/Animation.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/Animation.cpp -c -o ./build/Animation.o

./build/AnimationManager.o:./src/AnimationManager.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/AnimationManager.cpp -c -o ./build/AnimationManager.o

./build/CharacterAnimationSet.o:./src/CharacterAnimationSet.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/CharacterAnimationSet.cpp -c -o ./build/CharacterAnimationSet.o

./build/HPBar.o:./src/HPBar.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/HPBar.cpp -c -o ./build/HPBar.o

./build/BattleButton.o:./src/BattleButton.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/BattleButton.cpp -c -o ./build/BattleButton.o

./build/BattleEffects.o:./src/BattleEffects.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/BattleEffects.cpp -c -o ./build/BattleEffects.o

./build/ItemMenu.o:./src/ItemMenu.cpp
	${CC} ${COMPILER_FLAGS} ${INCLUDES} ./src/ItemMenu.cpp -c -o ./build/ItemMenu.o

clean:
	${RM} ./bin/main
	${RM} ${OBJECTS}