#include "Input.h"

Input::Input() {
	#define f std::fill
		f(keys, keys+16, 0); 		
	#undef f	
}

void Input::update(const SDL_Event& e) {
	switch(e.key.keysym.sym) {
		case SDLK_0:
			keys[0] = true;
		break;

		case SDLK_1:
			keys[1] = true;;
		break;

		case SDLK_2:
			keys[2] = true;
		break;

		case SDLK_3:
			keys[3] = true;
		break;

		case SDLK_4:
			keys[4] = true;
		break;

		case SDLK_5:
			keys[5] = true;
		break;

		case SDLK_6:
			keys[6] = true;
		break;

		case SDLK_7:
			keys[7] = true;
		break;

		case SDLK_8:
			keys[8] = true;
		break;
		case SDLK_a:
			keys[0xA] = true;
		break;

		case SDLK_b:
			keys[0xB] = true;
		break;
		case SDLK_c:
			keys[0xC] = true;
		break;
		case SDLK_d:
			keys[0xD] = true;
		break;
		case SDLK_e:
			keys[0xE] = true;
		break;
		case SDLK_f:
			keys[0xF] = true;
		break;
	}
}
