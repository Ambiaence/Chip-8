#pragma once
#include <iostream>
#include <SDL2/SDL.h>

class Input {
	public:
		Input();
		bool keys[16];
		void updateDown(const SDL_Event& e); 
		void updateUp(const SDL_Event& e); 
};
