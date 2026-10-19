#pragma once

#include <SDL3/SDL.h>

#include <cmath>

struct Vector2 {
	float x;
	float y;

	float sqrMagnitude() const { return x * x + y * y; }
	float magnitude() const { return std::sqrt(this->sqrMagnitude()); }
	Vector2 normalized() const {
		float mag = this->magnitude();
		if (mag == 0) {
			return Vector2(0, 0);
		}
		return *this / mag;
	}
	float dot(const Vector2& other) const { return this->x * other.x + this->y * other.y; }

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

	bool operator==(const Vector2& other) const { return this == &other || (x == other.x && y == other.y); }
	Vector2& operator=(const Vector2& other) {
		if (this != &other) {
			this->x = other.x;
			this->y = other.y;
		}
		return *this;
	}

	Vector2 operator*(float scalar) const { return Vector2(this->x * scalar, this->y * scalar); }
	Vector2& operator*=(float scalar) {
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	Vector2 operator/(float scalar) const { return Vector2(this->x / scalar, this->y / scalar); }
	Vector2& operator/=(float scalar) {
		this->x /= scalar;
		this->y /= scalar;
		return *this;
	}
};

class deltaTime {
	Uint64 lastTick;

   public:
	float get() {
		Uint64 currentTick = SDL_GetTicksNS();
		float deltaTime = (currentTick - lastTick) / 1000000.0f;
		lastTick = currentTick;
		return deltaTime;
	}

	explicit deltaTime(Uint64 firstTick) : lastTick(firstTick) {}
};
