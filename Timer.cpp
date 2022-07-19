#include "Timer.h"

Timer::Timer(const float& TimerMax, const bool& reverse){
	setTimerMax(TimerMax);
	setReversed(reverse);
}

bool Timer::timerOver(const float& dt){
	if (!reverse) {
		timer += dt;

		if (timer >= timerMax) {
			timer = 0.f;
			return true;
		}

		return false;
	}
	else {
		timer -= dt;

		if (timer <= 0.f) {
			timer = timerMax;
			return true;
		}

		return false;
	}
}

void Timer::setTimerMax(const float& NewTimerMax){
	timerMax = NewTimerMax;
}

void Timer::setReversed(const bool& reverse){
	this->reverse = reverse;

	reverse ? timer = timerMax : timer = 0.f;
}
