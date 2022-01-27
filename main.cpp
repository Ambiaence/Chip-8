#include <iostream>
unsigned char reg[16] = {0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,  
			0, 0, 0, 0};

unsigned int pc = 0; //Program counter
unsigned char mem[4096]; //Entire memory

bool debug = false;
bool standardInput = false;
//Takes a character and returns a four bit word, based on its hex equivalent, at the least significant bits of a new character. If the stream gives a bad character or 'T' then it will return a character to signify  that.

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
				mem[i] = (charOne << 4) | charTwo; //Might break compatibility with c++ implementations that don't have 8 bit char.

			//std::cout << "Output was: " <<  (int)mem[i] << std::endl;
		}
	}
}

