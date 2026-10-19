#pragma once

#include <SDL3/SDL.h>

#include <vector>

#include "physics.h"

namespace core {

const int OBJSIZE = 1;

struct Vector2 {
	float x = 0.0f;
	float y = 0.0f;
};

void draw(SDL_Renderer* renderer, std::vector<Physics::Object>& objects);
float getGroundLevel(SDL_Renderer* renderer);
}  // namespace core