#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <math.h>


#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f


struct Vector2 {
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f) :
		x(_x), y(_y) {}
	

	float MagnitudeSqr() { return pow(x, 2) * pow(y, 2); }

	float Magnitude() {
		return (float)sqrt(pow(x, 2)*pow(y, 2));
	}

	Vector2 Normalized() {
		float mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}


	Vector2 &operator +=(const Vector2& rhs) {
		x += rhs.x;
		y += rhs.y;

		return *this;
	}
	Vector2 &operator -=(const Vector2& rhs) {
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}
};

inline Vector2 operator +(const Vector2& lbs, const Vector2& rhs) {
	return Vector2(lbs.x + rhs.x, lbs.y + rhs.y);
}
inline Vector2 operator -(const Vector2& lbs, const Vector2& rhs) {
	return Vector2(lbs.x - rhs.x, lbs.y - rhs.y);
}
inline Vector2 operator *(const Vector2& lbs, const Vector2& rhs) {
	return Vector2(lbs.x * rhs.x, lbs.y * rhs.y);
}

inline Vector2 RotateVector(Vector2 vec, float angle) {
	float radAngle = (float)(angle*DEG_TO_RAD);
	return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) - vec.y * cos(radAngle)));
}

const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
const Vector2 VEC2_ONE = { 1.0f, 1.0f };
const Vector2 VEC2_UP = { 0.0f, 1.0f };
const Vector2 VEC2_RIGHT = { 1.0f, 0.0f };


#endif
