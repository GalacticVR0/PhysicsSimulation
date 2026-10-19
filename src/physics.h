#pragma once
#include <SDL3/SDL.h>

#include <vector>

#include "utils.hpp"
namespace Physics {
struct Object {
	Vector2 position{};
	Vector2 velocity{};
};

class PhysicsHandler {
   public:
	float gravity = 2.0f;

	void updateGravity(float deltaTime, std::vector<Object>& objects);
	void checkCollisions(std::vector<Object>& objects);
	void checkGroundCollisions(std::vector<Object>& objects, SDL_Renderer* renderer);
};
}  // namespace Physics