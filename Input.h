#pragma once
#include <iostream>
#include <SDL2/SDL.h>

class Input {
	public:
		Input();
		bool keys[16];
		void update(const SDL_Event& e); 
};
