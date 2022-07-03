#include "Sdl.h"

void closeSDL() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	SDL_Renderer* gRenderer = NULL;
	SDL_Window* window = NULL;
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
		SDL_Window* window = NULL;
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());}
		else {
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
}
