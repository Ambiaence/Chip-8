#include "Input.h"

Input::Input() {
	#define f std::fill
		f(keys, keys+16, 0); 		
	#undef f	
}

void Input::updateDown(const SDL_Event& e) {
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
		case SDLK_9:
			keys[9] = true;
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
	/*for(int i = 0; i < 4; i++) {
		for(int ii = i*4; ii < i*4+4; ii++ ) {
			std::cout << keys[ii] ;
		}
			std::cout << '\n';

	}*/
	
}
void Input::updateUp(const SDL_Event& e) {
	switch(e.key.keysym.sym) {
		case SDLK_0:
			keys[0] = false;
		break;
		case SDLK_1:
			keys[1] = false;;
		break;
		case SDLK_2:
			keys[2] = false;
		break;
		case SDLK_3:
			keys[3] = false;
		break;
		case SDLK_4:
			keys[4] = false;
		break;
		case SDLK_5:
			keys[5] = false;
		break;
		case SDLK_6:
			keys[6] = false;
		break;

		case SDLK_7:
			keys[7] = false;
		break;

		case SDLK_8:
			keys[8] = false;
		break;
		case SDLK_9:
			keys[9] = false;
		break;
		case SDLK_a:
			keys[0xA] = false;
		break;

		case SDLK_b:
			keys[0xB] = false;
		break;
		case SDLK_c:
			keys[0xC] = false;
		break;
		case SDLK_d:
			keys[0xD] = false;
		break;
		case SDLK_e:
			keys[0xE] = false;
		break;
		case SDLK_f:
			keys[0xF] = false;
		break;
	}
}
