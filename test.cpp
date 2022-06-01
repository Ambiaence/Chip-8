#include<iostream>

int main () {
	unsigned char test = 0x00;
	unsigned char best = 0xF0;
	unsigned char rest; 


	while (true) {
		test--;
		best-=2;
		rest = test - best;
		std::cout << "rest: " <<(int) rest << std::endl;
		std::cout << "cast raw " <<(int) test - (int) best << std::endl;
		std::cout << "cast parens " <<((int) test - (int) best) << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}
}
