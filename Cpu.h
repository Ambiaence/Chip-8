#pragma once

class Cpu 
{
	public:
		Cpu();
		unsigned char randByte(); 
		int tick();
		void connectToInput(bool *input);

		unsigned char reg[16];
		unsigned short stack[16];
		unsigned short pc;
		unsigned char screen[32][8];
		char temp;
		unsigned short ar;
		unsigned int sp; 
		unsigned char mem[4096]; 
		unsigned int im; //I reg
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

	private:
		bool *keys;
};
