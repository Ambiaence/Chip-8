#pragma once
#include <SDL2/SDL.h>

void sdlRenderPresent();
void closeSDL();
void drawPixel(int x, int y, bool value);
void render();
void sdlDrawScreen(unsigned char screen[32][8]);
int initSDL();
