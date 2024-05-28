#include <iostream>
#include <fstream>
#include <algorithm> 
#include <vector>

#include "Sdl.h"
#include "Input.h"
#include "Bitfun.h"
#include "Datapath.h"

#define START 0x200

bool debug = false;
bool file = false;
bool standardInput = false;
bool run = true;
bool sdl = false;
int temp;


int handleArguments(int argc, char **argv) {
	for(int x = 1; x < argc; x++) {
		if( argv[x][0] != '-') {
			std::cout << argv[x] << "argument must start with '-' and be followed by a single character. Terminating" << '\n';
			return -1; 
		} 

		if(argv[x][1] == 'd' || argv[x][1] == 'D') {
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
		std::cout << '\n';
	}	
	return 1;
}

int main(int argc, char **argv)  //#Main
{
	if (handleArguments(argc, argv) < 0) {
		return -1;		
	}

	Input input = Input();
	Datapath datapath = Datapath();
	datapath.connectToInput(input.keys);
	SDL_Event e;


	if(sizeof(short) != 2 or sizeof(char) != 1) {
		std::cout << "Datatype needed is not supported on your device.";
		return 0;
	}

	if(sdl) { 
		if (initSDL() == -1) {
			return -1;
		}
	}

	if(file) {		
		std::ifstream input("test.bin", std::ios::binary);
		std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

		int count = 0;

		for(auto iter = buffer.begin(); iter != buffer.end(); iter++) {
			printCharAsHex(*iter);
			datapath.mem[count++ + START] = *iter; 
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
				datapath.mem[i] = (charOne << 4) | charTwo; 
			//std::cout << "Output was: " <<  (int)mem[i] << std::endl;
		}
	}
		

	while(run) {
		while(SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT )
			{
				run = false;
			}  if (e.type == SDL_KEYDOWN) {  
				input.updateDown(e);
			} if (e.type == SDL_KEYUP) {  
				input.updateUp(e);
			}
		}

		if(sdl) {
			sdlDrawScreen(datapath.screen);
		}

		if(debug) {//Don't print DataPath Info if not in debug 
				for(int r = 0; r < 32; r++) {
					for(int c = 0; c < 8; c++) {
						printCharBits(datapath.screen[r][c]);
					}
					if(r < 16) {
						if(r < 10)	 
							std::cout << "|R" << r <<": " << (int)datapath.reg[r] << '\n';
						else 	
							std::cout << "|R" << (char)(r + ('A' - 10)) << ": "<<  (int)datapath.reg[r] <<  '\n';
					} else if(r == 16) {
						std::cout << "|SP: " << datapath.sp << '\n';
					} else if(r == 17) {
						std::cout << "|PC: "<< datapath.pc << "\n";
					} else if(r == 18) {
						std::cout << "|I"<< datapath.im << "\n";
					} else  { //19 or greater {
						std::cout << "|MEM|"; 
						printCharAsHex(datapath.mem[datapath.pc + (r - 19)*2]);
						printCharAsHex(datapath.mem[datapath.pc + (r - 19)*2 + 1]);
						std::cout << '\n';
					}
				}		 
		}

		if(debug)
			if(temp-- <= 0) 	
				std::cin >> temp;

		datapath.tick();
		sdlRenderPresent();
	}
}

