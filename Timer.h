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
	int timeCounter;

private:
	c::steady_clock::time_point startTime;
	c::steady_clock::time_point currentTime;
	std::chrono::milliseconds rate = 16ms;
	c::duration<double> diff;
};
#undef c 
