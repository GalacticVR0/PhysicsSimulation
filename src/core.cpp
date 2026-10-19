#include "core.h"

#include "physics.h"

namespace core {
void draw(SDL_Renderer* renderer, std::vector<Physics::Object>& objects) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (const auto& obj : objects) {
		SDL_FRect rect{ obj.position.x, obj.position.y, 10.0f, 10.0f };
		SDL_RenderFillRect(renderer, &rect);
	}
}

float getGroundLevel(SDL_Renderer* renderer) {
	int width = 0;
	int height = 0;
	if (SDL_GetRenderOutputSize(renderer, &width, &height)) {
		return static_cast<float>(height) - 10.0f;
	}
	return 0.0f;
}
}  // namespace core