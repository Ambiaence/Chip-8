#include <iostream>

unsigned char charToFourBitWord(unsigned char byte) //Takes a character and retuns a four bit word at the least sigificant bits of character
{				
	if(byte >= 'A' && byte <= 'F')
		return byte - 'A' + 10 ;
	else if(byte >= '0' && byte <= '9')
		return byte - '0';
	else return 'f'; //Returns a failure of the data was not within the correct range
}

int main() 
{
	unsigned char reg[16] = {0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,  
			0, 0, 0, 0};

	unsigned char mem[4096];

	unsigned char charOne; //Current characcter to be parsed into a 4 bit word
	unsigned char charTwo; //Current characcter to be parsed into a 4 bit word
		
	for(int i = 0; i < 4096 &&  ; i++) {
		if((charOne = charToFourBitWord(charOne)) == 'f'){
			std::cout << "BYTE MUST BE A HEX VALUE" << std::endl;
			return -1;
		}
			
		if((charTwo = charToFourBitWord(charTwo)) == 'f') {
			std::cout << "BYTE MUST BE A HEX VALUE" << std::endl;
			return -1;
		}
		mem[i] = (charOne << 4) | charTwo;

		std::cout << "Output was: " <<  (int)mem[i] << std::endl;
	}
		
							

}

