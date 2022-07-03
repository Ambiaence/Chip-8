#include <SDL2/SDL.h>

SDL_Renderer* gRenderer;
SDL_Window* window;

void closeSDL();
void drawPixel(int x, int y, bool value);
void render();
int initSDL();
