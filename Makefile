CC = g++
CFLAGS = -Wall -g
INCLUDES = -I /usr/include/SDL2
RM = rm -f

OBJECTS = Animal.o Narwhal.o

all: ${OBJECTS}
	$(CC) ${CFLAGS} ${INCLUDES} main.cpp ${OBJECTS} -lSDL2main -lSDL2 -o main


#all:
#	$(CC) $(CFLAGS) main.cpp -o main

Animal.o:Animal.cpp
	$(CC) ${CFLAGS} Animal.cpp -c -o Animal.o

Narwhal.o:Narwhal.cpp
	$(CC) ${CFLAGS} Narwhal.cpp -c -o Narwhal.o


clean:
	$(RM) main
	$(RM) $(OBJECTS)