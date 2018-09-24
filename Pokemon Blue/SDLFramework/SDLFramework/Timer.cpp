#include "Timer.h"


//Singleton
Timer* Timer::sInstance = nullptr;
Timer* Timer::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Timer();
	}

	return sInstance;
}

void Timer::Release() {
	delete sInstance;
	sInstance = nullptr;
}

Timer::Timer() {
	Reset();
	mTimeScale = 1.0f;
}

Timer::~Timer() {}

void Timer::Reset() {
	mStartTicks = SDL_GetTicks();
	mElapsedTicks = 0;
	mDeltaTime = 0.0f;
}

void Timer::TimeScale(float t) {
	mTimeScale = t;
}

float Timer::DeltaTime() {
	return mDeltaTime;
}

float Timer::TimeScale() {
	return mTimeScale;
}

void Timer::Update() {
	mElapsedTicks = SDL_GetTicks() - mStartTicks;

	//Converting milliseconds to seconds
	mDeltaTime = mElapsedTicks * 0.001f;
}
