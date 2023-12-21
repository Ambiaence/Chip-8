#pragma once
#include <time.h>
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;
namespace chrono = std::chrono;

class Timer {
public:
	Timer();
	void update();
	void setCounter(int newTime);
	int timeCounter;

private:
	chrono::steady_clock::time_point startTime;
	chrono::steady_clock::time_point currentTime;
	chrono::milliseconds rate = 16ms;
	chrono::duration<double> diff;
};
