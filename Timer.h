#pragma once
class Timer{
private:
	float timer;
	float timerMax;
	bool reverse;

public:
	Timer() { };
	Timer(const float& TimerMax, const bool& reverse = false);

	void setTimerMax(const float& NewTimerMax);
	void setReversed(const bool& reverse);
	void reset() { timer = 0.f; };

	bool timerOver(const float& dt);

	const float& getTimer() const { return timer; };
	const float& getTimerMax() const { return timerMax; };
};

