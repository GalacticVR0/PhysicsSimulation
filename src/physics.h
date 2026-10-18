#pragma once

#include <vector>
#include "core.h"

namespace Physics {
    

    struct PhysicsObject {
        core::Vector2 position{};
        core::Vector2 velocity{};
    };

    const float GRAVITY = 1.0f;

    void updateGravity(float deltaTime, std::vector<PhysicsObject>& objects);
}