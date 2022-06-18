#include <algorithm>
#include <iostream>

#include "Cpu.h"

Cpu::Cpu() {
	sp = 0;
	ar = 0;
	im = 0;
	pc = 0x200;  

	std::fill(&screen[0][0], &screen[0][0] + sizeof(screen) / sizeof(screen[0][0]),0);	
	std::fill(&reg[0], &reg[0] + sizeof(reg), 0);
	std::fill(&mem[0], &reg[0] + sizeof(mem), 0);
	std::fill(&stack[0], &stack[0] + sizeof(stack), 0);
}

unsigned char Cpu::randByte() {
	return 0x33;
}

int Cpu::tick() {
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
	return 1;
}