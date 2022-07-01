#pragma once
#include "Timer.h"

class Datapath 
{
	public:
		Datapath();
		unsigned char randByte(); 
		int tick();
		void connectToInput(bool *input);

	
		unsigned char reg[16];
		unsigned short stack[48];
		unsigned short pc;
		unsigned char screen[32][8];
		char temp;
		unsigned short ar;
		unsigned int sp; 
		unsigned char mem[4096]; 
		unsigned int im; //I reg

	private:
		Timer timer = Timer();	
		unsigned char vx;
		unsigned char vy;
		unsigned char kk;
		unsigned char key;
		unsigned char head; 
		unsigned char tail;
		unsigned char a;
		unsigned char b;
		unsigned char c;
		unsigned char d;
		bool *keys;
};
