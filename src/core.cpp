#include "core.h"
#include "physics.h"

namespace core {
    void draw(SDL_Renderer *renderer, std::vector<Physics::PhysicsObject> &objects) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (const auto &obj : objects) {
            SDL_FRect rect{obj.position.x, obj.position.y, 10.0f, 10.0f};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}