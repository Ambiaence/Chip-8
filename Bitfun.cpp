#include "Bitfun.h"
#include <iostream>

void printCharBits(const unsigned char block) {
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

void printCharAsHex(const unsigned char& block) {
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
