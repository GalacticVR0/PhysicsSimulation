#include "physics.h"

namespace Physics {
    void updateGravity(float deltaTime, std::vector<PhysicsObject>& objects) {
        if (deltaTime <= 0.0f) {
            return;
        }
        for (PhysicsObject& object : objects) {
            object.velocity.x += 0.0f * deltaTime;
            object.velocity.y += GRAVITY * deltaTime;
            object.position.x += object.velocity.x * deltaTime;
            object.position.y += object.velocity.y * deltaTime;
        }
    }


    void checkCollisions(std::vector<PhysicsObject>& objects, SDL_Renderer *renderer) {
        for (PhysicsObject& object : objects) {
            float groundLevel = core::getGroundLevel(renderer);
            if (object.position.y >= groundLevel) {
                object.position.y = groundLevel;
                object.velocity.y = 0.0f; // Stop vertical movement
            }
        }
    }
}