#pragma once

#include <SDL3/SDL.h>
#include <vector>

namespace Physics {
    struct PhysicsObject;
}

namespace core {
    struct Vector2 {
        float x = 0.0f;
        float y = 0.0f;
    };

    void draw(SDL_Renderer *renderer, std::vector<Physics::PhysicsObject> &objects);
    float getGroundLevel(SDL_Renderer *renderer);
}