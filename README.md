# Info
The following is an implementation a chip 8 virtual machine.
The project runs and is in a debugging and refactoring stage. Debug mode is used to test the implementation of the instruction set. SDL is used to handle I/O.
I am not using any reference outside of the specifications of chip-8 as to gain independence on these sorts of projects(Chip-8 is too small to look up any sort of tutorial), so do not look at this project for best practice. You won't find anything pedagogical here. 

# Compile

Use the makefile to compile. To compile with gdb debugger set DEBUG=1 .

Windows and Mac users might need to replace #include <SDL2/SDL.h> with #include <SDL.h>

```
make DEBUG=1
```

# Execution and flags

```
./chip8 -f -s -d
```

-d is for debug
-s is for SDL
-f loads machine code from test.bin located int he same folder.

# Problems

Bit manipulation is perhaps platform dependent.  

# Planned work

Interperate op code with switch statements

Compile different includes depending on platform

# Maybe?

webasm implementation
