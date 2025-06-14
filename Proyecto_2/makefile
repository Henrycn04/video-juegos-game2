CC=g++
STD=-std=c++17
CFLAGS=-Wall -Wextra
INC_PATH=-I"./libs"
SRC=$(wildcard src/**/*.cpp src/*.cpp)
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3
EXEC=game_engine

.PHONY: build run clean

build:
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) $(SRC) $(LFLAGS) -o $(EXEC)

run: 
	./$(EXEC)

clean:
	rm -f $(EXEC)
