#include <iostream>
#include <algorithm> 

unsigned char reg[16] = {0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,  
			0, 0, 0, 0};

unsigned char screen[32][8] = {}; //Screen is 64*32 
unsigned int pc = 0; //Program counter
unsigned char mem[4096] = {}; //Entire memory

bool debug = false;
bool standardInput = false;
bool run = true;
//Takes a character and returns a four bit word, based on its hex equivalent, at the least significant bits of a new character. If the stream gives a bad character or 'T' then it will return a character to signify  that.

void printCharBytes(const unsigned char& block) { //This might need to be switched around depending on the chip-8 graphics specification 
	std::cout << (bool)(block & 0b10000000);
	std::cout << (bool)(block & 0b01000000);
	std::cout << (bool)(block & 0b00100000);
	std::cout << (bool)(block & 0b00010000);
	std::cout << (bool)(block & 0b00001000);
	std::cout << (bool)(block & 0b00000100);
	std::cout << (bool)(block & 0b00000010);
	std::cout << (bool)(block & 0b00000001);}

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

	if(upper < 10) 
		std::cout << (int)lower;
	else
		std::cout << (char)(lower + 'A' - 10);
}

int main(int argc, char **argv) 
{
	for(int x = 1; x < argc; x++) {
		if(argv[x][0] != '-') {
			std::cout << argv[x] << "argument must start with '-' and be followed by a single character. Terminating";
			return -1; 
		}
		else if(argv[x][1] == 'd' || argv[x][1] == 'D') {
			debug = true;
			std::cout << "Debug mode is enabled. Registers and Memory after PC will be displayed. " << std::endl;
		}
		else if(argv[x][1] == 'i' || argv[x][1] == 'I') {
			standardInput = true;
			std::cout << "Standard input mode is enabled. System memory will be loaded from stdin" << std::endl;
		}
		else {
			std::cout << argv[x] <<" is not a legal argument. Terminating" << std::endl;
			return -1;
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
				mem[i] = (charOne << 4) | charTwo; 
			//std::cout << "Output was: " <<  (int)mem[i] << std::endl;
		}

		while(run) {
			if(debug) 
			{
				for(int r = 0; r < 32; r++) {
					for(int c = 0; c < 8; c++) {
						printCharBytes(screen[r][c]);
					}
					if(r < 16) {
						if(r < 10)	 
							std::cout << "|R" << r <<": " << (int)reg[r] << '\n';
						else 	
							std::cout << "|R" << (char)(r + ('A' - 10)) << ": "<<  (int)reg[r] <<  '\n'; //Will the compiler simplify literal arithmatic A
					} else if(r == 16) {
						std::cout << "|\n";
					} else if(r == 17) {
						std::cout << "|PC: "<< pc << "\n";
					} else if(r == 18) {
						std::cout << "|" << "\n";
					} else  { //19 or greater {
						std::cout << "|MEM|"; 
						printCharToHex(mem[pc + (r - 19)*2]);
						printCharToHex(mem[pc + (r - 19)*2 + 1]);
						std::cout << '\n';
					}
				}		 
			}
		if( (mem[pc] >> 4) == 11) {
			pc = (mem[pc] & 0x0f) << 4 + mem[pc+1];
			std::cout << pc << std::endl;
		} else if (mem[pc] == 0x00 && mem[pc+1] == 0xE0) {
			std::fill(
				&screen[0][0],
				&screen[0][0] + sizeof(screen) / sizeof(screen[0][0]),
				0);
			std::cout << "Screen clear";
			pc = pc+2;
		} else {pc = pc + 2;}
		std::cin >> screen[0][0];
		}
		

	}
}

