#https://stackoverflow.com/questions/20308661/linking-sdl-image-in-make-file
OBJS = BonusGame.cpp Button.cpp Chest.cpp Constants.h Figure.cpp Game.cpp GameManager.cpp GamePanel.cpp Info.cpp Intro.cpp Label.cpp Lines.cpp main.cpp Outro.cpp pugixml.cpp Reel.cpp Slot.cpp State.cpp TextField.cpp Win.cpp

CC = g++

LIBS = -L/usr/include/SDL_image -L/usr/include/SDL_mixer -L/usr/include/SDL_ttf

COMPILER_FLAGS = -w 

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = main

all : $(OBJS)
		$(CC) $(OBJS) $(LIBS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

