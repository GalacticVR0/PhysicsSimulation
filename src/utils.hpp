#pragma once

struct Vector2 {
	float x = 0.0f;
	float y = 0.0f;
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

	deltaTime(Uint64 firstTick) : lastTick(firstTick) {}
};