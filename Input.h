#pragma once
#include <iostream>
#include <SDL2/SDL.h>

class Input {
	public:
		Input();
		void updateDown(const SDL_Event& e); 
		void updateUp(const SDL_Event& e); 
		bool keys[16];
};
