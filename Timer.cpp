#include "Timer.h"

#define c std::chrono::steady_clock


Timer::Timer() {
	timeCounter = 0;
}

void Timer::update() {
	if(timeCounter != 0) {
		currentTime = c::now();
		diff = currentTime - startTime;
		if((diff) < rate)
			return;
		else {
			startTime = currentTime;
			timeCounter--;
		}  
	}
}

void Timer::setCounter(int newTime) {
	startTime = c::now();
	timeCounter = newTime;
}
