#include "Sdl.h"

SDL_Renderer* gRenderer;
SDL_Window* window;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

void sdlRenderPresent() {
	SDL_RenderPresent(gRenderer);
}

void sdlDrawScreen(unsigned char screen[32][8]) {
	for (int r = 0; r < 32; r++) {
		for (int c = 0; c < 64; c++) {
			if( ( screen[r][c/8] & (0b10000000 >> c%8)) > 0) {
				drawPixel(c*10, r*10, true);
			} else {
				drawPixel(c*10, r*10, false);
			}
		}
	}
}

void closeSDL() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	gRenderer = NULL;
	window = NULL;
	SDL_Quit();
}

void drawPixel(int x, int y, bool value) {
	SDL_Rect fillRect = {x, y, x+9, y+9};
	if(value)
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	else
		SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderFillRect( gRenderer, &fillRect );
}

int initSDL() {
	bool success = false;
	SDL_Window* window = NULL;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	} else {
		window = SDL_CreateWindow( "CHIP-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		} else {
			SDL_UpdateWindowSurface( window );

			//Create renderer for window
			gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

			if( gRenderer == NULL ) {
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			} else {
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				success = true;
			}
		}
	}
	if(not success) {
		closeSDL();
		return -1;
	}
	return success;
}
