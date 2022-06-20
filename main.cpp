#include <iostream>
#include <time.h>
#include <fstream>
#include <algorithm> 
#include <vector>
#include <SDL2/SDL.h>

#include "Input.h"
#include "Cpu.h"
#define START 0x200

<<<<<<< HEAD
//Unstable test
unsigned char reg[16] = {0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,  
			0, 0, 0, 0};

unsigned short stack[16] = {0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,  
			0, 0, 0, 0};

unsigned char screen[32][8] = {}; //Screen is 64*32 each char can store 8 pixels

unsigned short pc = 0; //Program counter
 
clock_t oldTime;
clock_t newTime;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

SDL_Renderer* gRenderer = NULL;
SDL_Window* window = NULL;

char temp;
unsigned short ar = 0;
unsigned int sp = 0; //stack pointer
unsigned char mem[4096] = {}; //Entire memory
unsigned int im; //I reg
unsigned char vx; 
unsigned char vy; 
unsigned char kk; 
unsigned char key;

unsigned char head; //Some of these variables are redundant perhaps I can use a union.
unsigned char tail;
unsigned char a;
unsigned char b;
unsigned char c;
unsigned char d;

bool success;
=======
>>>>>>> unstable
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
<<<<<<< HEAD

	clock_t start = clock();						
	std::cout << start << '\n';

=======
	Input input = Input();
	Cpu cpu = Cpu();
	cpu.connectToInput(input.keys);
	SDL_Event e;

	bool success;
>>>>>>> unstable
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
<<<<<<< HEAD

		//Bad Paser? Good Parser! 
		//One instruction abcd Big endian
		//head = ab
		//tail = cd

		head = mem[pc];
		tail = mem[pc+1];
		a = head >> 4;
		b = (head & 0x0F);
		d = (tail & 0x0F);
		c = tail >> 4;
		vx = b; //register of index x
		vy = c;
		kk = tail; //Value of last byte

		if(temp == 'c') { //Jump + v0 Bnnn
			closeSDL();			
			return 0;
		} else if(a  == 1) { //Jump + v0 Bnnn
			pc = (b << 8) | tail; //b = n1 tail = n2n3
		} else if (head == 0x00 and tail == 0xE0) { //clear
			std::fill(
				&screen[0][0],
				&screen[0][0] + sizeof(screen) / sizeof(screen[0][0]),
				0);
			pc = pc+2;
		} else if (head == 0x00 and tail == 0xEE) { //RET from subroutine
			pc = stack[sp];			
			sp+=-1;
		} else if (a == 2) { //execute subroutine
			sp++; 
			stack[sp] = pc + 2;
			pc = (b << 8) | tail; //b = n1 tail = n2n3
		} else if (a == 3) {//3XKK Compare and skip
			if (reg[vx] == kk) 
				pc = pc+4;//Skip next instruction
			else
				pc = pc+2;//Proceed as normal probably a brancear
		} else if (a == 4) {//3XKK Compare and skip
			if (reg[vx] != kk) 
				pc = pc+4;//Skip next instruction
			else
				pc = pc+2;//Proceed as normal probably a brancear
		} else if (a == 5) {//5Xy0 Compare and skip if vx=vy
			if(reg[vx] == reg[vy]) 
				pc = pc+4;
			else
				pc = pc+2;
		} else if (a == 6) {//6XKK Compare and skip
			reg[vx] = kk;
			pc = pc + 2;
		} else if (a == 7) {//7XKK add 
			reg[vx] = reg[vx] + kk;
			pc = pc + 2;
		} else if (a == 8) {//8XY? load 
			if (d == 0) {
				reg[vx] = reg[vy];//load val of reg x into y reg y
			} else if (d == 1) { //Vx = vx or vy
				reg[vx] = reg[vx] | reg[vy];
			} else if (d == 2) { //Vx = vx or vy
				reg[vx] = reg[vx] & reg[vy];
			} else if (d == 3) { //Vx = vx or vy
				reg[vx] = reg[vx] ^ reg[vy]; //
			} else if (d == 4) { //Vx = vx or vy
				reg[vx] = reg[vx] + reg[vy];
				if (((int)reg[vx] + (int) reg[vy]) > 255) //if A borrow occured
					reg[0xF] = 0x01;
				else
					reg[0xF] = 0x00;
			} else if (d == 5) { //Vx = vx or vy
				reg[vx] = reg[vx] - reg[vy]; 
				std::cout <<  (int) reg[vx] - (int) reg[vy]   << std::endl;
				if(((int) reg[vx] - (int) reg[vy]) < 0)
					reg[0xF] = 0x00;
				else
					reg[0xF] = 0x01;
			} else if (d == 6) { //Vx = vx or vy
				reg[0xF] = reg[vy] & 0x01; //VF equals lest significant bit of vy
				reg[vx] = reg[vy] > 1; //The rest is shifted to vx
			} else if (d == 7) { //Vx = vx or vy
				reg[vx] = reg[vy] - reg[vx]; 
				if(((int) reg[vy] - (int) reg[vx]) < 0) //Check for overflow
					reg[0xF] = 0x00;
				else
					reg[0xF] = 0x01;
			} else if (d == 0xE) { //Vx = vx or vy
				reg[0xF] = reg[vy] & 0x1;
				reg[vx]	= reg[vy] << 1;
			}
			pc = pc + 2;
		} else if (a == 9) {//9XY0 Not implemented
			if(reg[vx] != reg[vy]) 
				pc = pc+4;
			else 
				pc = pc+2;
		} else if (a == 0xA) {//ANNN
			im = (b << 8) | tail; //b = n1 tail = n2n3
			pc = pc + 2;
		} else if (a == 0xB) {//BNNN
			pc =  ((b << 8) | tail) + reg[0]; //pc = nnn+v0
		} else if (a == 0xC) {//CXKK  vx = rand() & kk 
			reg[vx] = randByte() & kk;
			pc = pc+2;
		} else if (a == 0xD) {//CXKK  vx = rand() & kk 
			int x = reg[vx]/8;
			int y = reg[vy];
			int offset = reg[vx]%8;
			unsigned char partA; 
			unsigned char partB; 
			unsigned char tempA; 
			unsigned char tempB; 
			
			//If it goes from set to unset then  
			//Get map of pixels that are set or it with pixels that changed

			for (int i = 0; i < d; i++) { 
				partA = mem[im+i] >> offset;
				partB = mem[im+i] << (8 - offset);

				tempA = screen[y+i][x] ^ partA;
				tempB = screen[y+i][x+1] ^ partB;

				if(((tempA ^ screen[y+i][x]) & screen[y+i][x]) == 0)// If a set pixel is made unset. 
					reg[0xF] = 0;
				else 
					reg[0xF] = 1;

				if(((tempB ^ screen[y+i][x+1]) & screen[y+i][x+1]) == 0)// If a set pixel is made unset. 
					reg[0xF] = 0;
				else 
					reg[0xF] = 1;
				screen[y+i][x] = screen[y+i][x] ^ partA; //clear old part and save unchanged
				screen[y+i][x+1] = screen[y+i][x+1] ^ partB; //clear old part and save unchanged
			}
			pc = pc+2;
		} else if (a == 0xE) {//EX?? 
			if(tail == 0x9E)  {
				if(key == reg[vx]) 
					pc = pc+4;
				else
					pc = pc+2;
			} else if(tail == 0xA1)  {
				if(key != reg[vx]) 
					pc = pc+4;
				else
					pc = pc+2;
			} else {
				pc = pc + 2;
			}
		} else if (a == 0xF) {//EX?? 
			if(tail == 0x07) {

			} else if (tail == 0x0A) {

			} else if (tail == 0x15) {

			} else if (tail == 0x18) {

			} else if (tail == 0x1E) {
				im = im + vx;
			} else if (tail == 0x33) {
				mem[im] = reg[vx] / 100;  // 3
				mem[im+1] = (reg[vx] % 100) / 10;  // 2
				mem[im+2] = (reg[vx] % 10);  //1
			} else if (tail == 0x55) {
				for( int i = 0; i <= vx; i++) {
					mem[im + i] = reg[i];
				}
				im = im + vx + 1;

			} else if (tail == 0x65) {
				for( int i = 0; i <= vx; i++) {
					reg[i] = mem[im + i];
				}
				im = im + vx + 1;
			}
				pc = pc+2;
		} else if(mem[pc] == 0x10) { 
				pc = (mem[pc] & 0x0f) << 4 + mem[pc+1];
		} else {
			pc = pc + 2;
	}
=======
		if(debug)
			std::cin >> temp;

			cpu.tick();
>>>>>>> unstable
			SDL_RenderPresent(gRenderer);
			std::cin >> temp;
			//while((newTime = clock()) -  oldTime < 1000);
			oldTime = newTime;


	}	
}
