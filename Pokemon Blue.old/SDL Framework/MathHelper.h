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

	// Square root of magnitude
	float MagnitudeSqr() {
		return x*x + y*y;
	}

	float Magnitude() {
		return (float)sqrt(x*x + y*y);
	}

	// Normalizing
	Vector2 Normalized() {
		float mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}

	Vector2& operator +=(const Vector2& rhs) {
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2& operator -=(const Vector2& rhs) {
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}
};

inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}

// But learn how to do division through multiplication
inline Vector2 operator /(const Vector2& lhs, const Vector2& rhs) {
	return Vector2(lhs.x / rhs.x, lhs.y / rhs.y);
}

inline Vector2 RotateVector(Vector2& vec, float angle) {
	float radAngle = (float)(angle*DEG_TO_RAD);
	return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}


const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
const Vector2 VEC2_ONE = { 1.0f, 1.0f };
const Vector2 VEC2_UP = { 0.0f, 1.0f };


#endif // !MATH_HELPER