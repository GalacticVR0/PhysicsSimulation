#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <imgui.h>

#include <vector>

#include "physics.h"

struct AppState {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::vector<Physics::PhysicsObject> objects;
};

SDL_AppResult SDL_AppInit(void** appstate, int, char**) {
	auto* state = new AppState{};
	if (state == nullptr) {
		return SDL_APP_FAILURE;
	}

	*appstate = state;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("Physics", 1280, 720, 0, &state->window, &state->renderer)) {
		SDL_Log("Failed to create window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	auto* state = static_cast<AppState*>(appstate);
	switch (event->type) {
		case SDL_EVENT_QUIT:
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			return SDL_APP_SUCCESS;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event->button.button == SDL_BUTTON_LEFT) {
				core::Vector2 position{ event->button.x, event->button.y };
				state->objects.push_back(Physics::PhysicsObject{ position, core::Vector2{ 0.0f, 0.0f } });
			}
			break;
		default:
			break;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	auto* state = static_cast<AppState*>(appstate);

	SDL_SetRenderDrawColor(state->renderer, 18, 24, 32, 255);
	SDL_RenderClear(state->renderer);

	// Update physics
	float deltaTime = 1.0f / 60.0f;	 // Assuming a fixed time step for simplicity
	Physics::updateGravity(deltaTime, state->objects);
	core::draw(state->renderer, state->objects);
	Physics::checkGroundCollisions(state->objects, state->renderer);

	SDL_RenderPresent(state->renderer);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult) {
	auto* state = static_cast<AppState*>(appstate);
	if (state != nullptr) {
		SDL_DestroyRenderer(state->renderer);
		SDL_DestroyWindow(state->window);
		delete state;
	}
	SDL_Quit();
}
