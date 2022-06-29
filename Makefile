
ifeq ($DEBUG), 1)
	OPTS = -g
endif

OBJS = main.cpp Cpu.cpp Input.cpp Timer.cpp 

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2

OBJ_NAME = chip8

all : $(OBJS)
	$(CC) $(OBJS) $(COMILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
