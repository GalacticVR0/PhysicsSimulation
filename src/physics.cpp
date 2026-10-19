#include "physics.h"

#include "core.h"

using namespace Physics;
void PhysicsHandler::updateGravity(float deltaTime, std::vector<Physics::Object>& objects) {
	if (deltaTime <= 0.0f) {
		return;
	}
	for (Physics::Object& object : objects) {
		object.velocity.x += 0.0f * deltaTime;
		object.velocity.y += this->gravity * deltaTime;
		object.position.x += object.velocity.x * deltaTime;
		object.position.y += object.velocity.y * deltaTime;
	}
}

void PhysicsHandler::checkCollisions(std::vector<Physics::Object>& objects) {
	// Check collisions using AABB (Axis-Aligned Bounding Box) method with other objects
	for (Physics::Object& object : objects) {
		for (Physics::Object& other : objects) {
			if (&object == &other) {
				continue;  // Skip self-collision
			}
			if (object.position.x < other.position.x + core::OBJSIZE &&
				object.position.x + core::OBJSIZE > other.position.x &&
				object.position.y < other.position.y + core::OBJSIZE &&
				object.position.y + core::OBJSIZE > other.position.y) {
				if (object.position.y < other.position.y) {
					// Object is above the other object
					object.position.y = other.position.y - core::OBJSIZE;
					object.velocity.y = 0.0f;  // Stop vertical movement
				} else {
					// Object is below the other object
					object.position.y = other.position.y + core::OBJSIZE;
				}
			}
		}
	}
}

void PhysicsHandler::checkGroundCollisions(std::vector<Physics::Object>& objects, SDL_Renderer* renderer) {
	for (Physics::Object& object : objects) {
		float groundLevel = core::getGroundLevel(renderer);
		if (object.position.y >= groundLevel) {
			object.position.y = groundLevel;
			object.velocity.y = 0.0f;  // Stop vertical movement
		}
	}
};