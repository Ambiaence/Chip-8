#include <iostream>
#include <fstream>
#include <algorithm> 
#include <vector>
#include <SDL2/SDL.h>

#include "Input.h"
#include "Cpu.h"
#define START 0x200

bool debug = false;
bool file = false;
bool standardInput = false;
bool run = true;
bool sdl = false;

SDL_Renderer* gRenderer;
SDL_Window* window;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;
char temp;

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

void printCharBytes(const unsigned char block) {
	for( int i = 0; i < 8; i++)  
		std::cout << (bool)(block & (0x10000000 >> i));
}

unsigned char charToFourBitWord(unsigned char byte) 
{				
	if(byte >= 'A' && byte <= 'F')
		return byte - 'A' + 10 ; //returns a value 10-15
	else if(byte >= '0' && byte <= '9')
		return byte - '0'; //Returns a value 0-9
	else if(byte == 'T')
		return 'T'; //signal to stop reading form standard input
	else 
		return 'f'; //signal that data is meaningless 
}

void printCharToHex(const unsigned char& block) {
	char upper = (block >> 4);
	char lower = (block & 0x0F);

	if(upper < 10) 
		std::cout << (int)upper;
	else
		std::cout << (char)(upper + 'A' - 10);
	if(lower < 10) 
		std::cout << (int)lower;
	else
		std::cout << (char)(lower + 'A' - 10);
}

int main(int argc, char **argv)  //#Main
{
	Input input = Input();
	Cpu cpu = Cpu();
	cpu.connectToInput(input.keys);
	SDL_Event e;

	bool success;
	if(sizeof(short) != 2 or sizeof(char) != 1)
		std::cout << "Datatype needed is not supported on your device.";

	for(int x = 1; x < argc; x++) {
		if(argv[x][0] != '-') {
			std::cout << argv[x] << "argument must start with '-' and be followed by a single character. Terminating";
			return -1; 
		} else if(argv[x][1] == 'd' || argv[x][1] == 'D') {
			debug = true;
			std::cout << "Debug mode is enabled. Registers and Memory after PC will be displayed. " << std::endl;
		} else if(argv[x][1] == 'f' || argv[x][1] == 'F') {
			if(standardInput) {
				std::cout << "You can't read memory from standard input and a binarie. Terminating\n";
				return -1;
			}
			file = true;
			std::cout << "File mode is enabled." << std::endl;
		} else if(argv[x][1] == 'i' || argv[x][1] == 'I') {
			standardInput = true;
			std::cout << "Standard input mode is enabled. System memory will be loaded from stdin" << std::endl;
		} else if(argv[x][1] == 's' || argv[x][1] == 'S') {
			sdl = true;
			std::cout << "Sdl will attempt to start." << std::endl;
		} else {
			std::cout << argv[x] <<" is not a legal argument. Terminating" << std::endl;
			return -1;
		}
	}

	if(sdl) { 
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

		if( not success) { 
			closeSDL();		
			return -1;
		}
	}

	if(file) {		
		std::ifstream input("test.bin", std::ios::binary);
		std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

		int count = 0;

		for(auto iter = buffer.begin(); iter != buffer.end(); iter++) {
			printCharToHex(*iter);
			cpu.mem[count++ + START] = *iter; 
		}
	}

	if(standardInput) {
		for(int i = 0, end = 0; (i < 4096) && (!end); i++) {
			char charOne;
			char charTwo;

			do {
				std::cin >> charOne;
			} while(isspace(charOne));

			do {
				std::cin >> charTwo;
			} while(isspace(charOne));

			if((charOne = charToFourBitWord(charOne)) == 'f'){ 
				std::cout << "CHAR MUST BE A HEX VALUE" << std::endl;
				return -1;
			} 

			if((charTwo = charToFourBitWord(charTwo)) == 'f') {
				std::cout << "CHAR MUST BE A HEX VALUE" << std::endl;
				return -1;
			}
			if(charOne == 'T' || charTwo == 'T')
				end = 1;	

			if(!end)
				cpu.mem[i] = (charOne << 4) | charTwo; 
			//std::cout << "Output was: " <<  (int)mem[i] << std::endl;
		}
	}
			while(run) {
				while(SDL_PollEvent( &e ) != 0 ) {
					if( e.type == SDL_QUIT )
					{
						run = false;
					}  
					if (e.type == SDL_KEYDOWN) {  
						input.update(e);
					}
				}

			if(sdl) {
				for (int r = 0; r < 32; r++) {
					for (int c = 0; c < 64; c++) { 
						if( ((unsigned) cpu.screen[r][c/8] & (0b10000000 >> c%8)) > 0) {
							drawPixel(c*10, r*10, true); 
						} else {
							drawPixel(c*10, r*10, false); 
						}
					}
				}
			}
			if(debug) {//Don't print if not in debug 
				for(int r = 0; r < 32; r++) {
					for(int c = 0; c < 8; c++) {
						printCharBytes(cpu.screen[r][c]);
					}
					if(r < 16) {
						if(r < 10)	 
							std::cout << "|R" << r <<": " << (int)cpu.reg[r] << '\n';
						else 	
							std::cout << "|R" << (char)(r + ('A' - 10)) << ": "<<  (int)cpu.reg[r] <<  '\n'; //Will the compiler scpu.implify literal arithmatic A?
					} else if(r == 16) {
						std::cout << "|\n";
					} else if(r == 17) {
						std::cout << "|PC: "<< cpu.pc << "\n";
					} else if(r == 18) {
						std::cout << "|I"<< cpu.im << "\n";
					} else  { //19 or greater {
						std::cout << "|MEM|"; 
						printCharToHex(cpu.mem[cpu.pc + (r - 19)*2]);
						printCharToHex(cpu.mem[cpu.pc + (r - 19)*2 + 1]);
						std::cout << '\n';
					}
				}		 
			}
		if(debug)
			std::cin >> temp;

			cpu.tick();
			SDL_RenderPresent(gRenderer);
	}	
}
