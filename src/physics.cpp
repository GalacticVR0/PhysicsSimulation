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
}