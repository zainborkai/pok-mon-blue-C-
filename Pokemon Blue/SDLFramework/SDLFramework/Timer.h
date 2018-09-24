#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer {
private:
	static Timer* sInstance;

	//Contains the time of the last reset
	unsigned int mStartTicks;

	//Stores the number of milliseconds since last reset
	unsigned int mElapsedTicks;

	//Stores the time elapsed since the last reset in seconds
	float mDeltaTime;

	//Can be used to speed up or slow down all entities that transform using it
	float mTimeScale;

public:
	static Timer* Instance();
	static void Release();
	void Reset();
	float DeltaTime();
	void TimeScale(float t = 1.0f);
	float TimeScale();
	void Update();

private:
	Timer();
	~Timer();
};

#endif // !TIMER_H
