ifeq ($(DEBUG), 1)
	COMPILER_FLAGS = -w -g
else
	COMPILER_FLAGS = -w
endif

OBJS = main.cpp Datapath.cpp Input.cpp Timer.cpp Bitfun.cpp

CC = g++

LINKER_FLAGS = -lSDL2

OBJ_NAME = chip8

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
