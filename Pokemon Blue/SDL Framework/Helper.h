#ifndef HELPER_H
#define HELPER_H

#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <ctime>



static int raffle() {
	return rand() % 100;
}

// ----------------------

static float longevity(float time, float delay, float period) {
	return std::min((time - delay) / std::max(0.00001f, period), 1.0f);
}

static float between(float left, float value, float right) {
	return value >= left && value <= right;
}

// *** NOT REALLY a coin flip (since you always pick heads)
static bool FlipACoin() {
	return raffle() < 50; // ??? <-- Note to self: SEED this randomness somewhere!
}

static int roundabout(int val, int max) {
	return ((val % max) + max) % max;
}

// *** Don't ask where this name came from.
static float modsicle(float val, float max) {
	return fmod(val, max) / max;
}


static std::string ToUppercase(std::string str) {
	for (auto & c : str) c = toupper(c);
	return str;
}


#endif
