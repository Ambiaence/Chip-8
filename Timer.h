#pragma once
#include <time.h>
#include <iostream>
#include <chrono>

#define c std::chrono

using namespace std::chrono_literals;

class Timer {
public:
	Timer();
	void update();
	void setCounter(int newTime);
	c::steady_clock::time_point startTime;
	c::steady_clock::time_point currentTime;
	c::duration<double> diff;
	std::chrono::milliseconds rate = 16ms;
	int timeCounter;
};
#undef c 
