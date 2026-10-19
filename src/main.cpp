#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <vector>

#include "core.h"
#include "physics.h"
#include "utils.hpp"

struct AppState {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::vector<Physics::Object> objects;

	deltaTime delta;
	Physics::PhysicsHandler physicsHandler;

	AppState(Uint64 firstTick) : delta(firstTick) {}
};

SDL_AppResult SDL_AppInit(void** appstate, int, char**) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	*appstate = new AppState(SDL_GetTicksNS());
	AppState& app = *static_cast<AppState*>(*appstate);

	if (!SDL_CreateWindowAndRenderer("Physics", 1280, 720, 0, &app.window, &app.renderer)) {
		SDL_Log("Failed to create window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL;	// Disable persistent window settings

	ImGui::StyleColorsDark();

	// Initialize ImGui renderer for sdl
	ImGui_ImplSDL3_InitForSDLRenderer(app.window, app.renderer);
	ImGui_ImplSDLRenderer3_Init(app.renderer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
	auto* state = static_cast<AppState*>(appstate);
	// Pass the event to ImGui for processing
	ImGui_ImplSDL3_ProcessEvent(event);

	if (ImGui::GetIO().WantCaptureMouse) {
		// Prevents SDL from processing mouse events intended for ImGui
		return SDL_APP_CONTINUE;
	}
	switch (event->type) {
		case SDL_EVENT_QUIT:
		case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
			return SDL_APP_SUCCESS;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event->button.button == SDL_BUTTON_LEFT) {
				Vector2 position{ event->button.x, event->button.y };
				state->objects.push_back(Physics::Object{ position, Vector2{ 0.0f, 0.0f } });
			}
			break;
		default:
			break;
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	auto& state = *static_cast<AppState*>(appstate);

	// Begin a new ImGui frame
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Physics Simulation", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::InputFloat("Gravity", &state.physicsHandler.gravity, 0.1f, 1.0f, "%.2f");
	ImGui::End();

	ImGui::Render();

	// Begin SDL rendering
	SDL_SetRenderDrawColor(state.renderer, 18, 24, 32, 255);
	SDL_RenderClear(state.renderer);

	core::draw(state.renderer, state.objects);

	// Update physics
	float deltaTime = state.delta.get() / 1000.0f;
	state.physicsHandler.updateGravity(deltaTime, state.objects);
	state.physicsHandler.checkCollisions(state.objects);
	state.physicsHandler.checkGroundCollisions(state.objects, state.renderer);

	// Add Imgui to the top of the SDL draw call
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), state.renderer);
	SDL_RenderPresent(state.renderer);
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult) {
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	auto& state = *static_cast<AppState*>(appstate);
	if (&state) {
		SDL_DestroyRenderer(state.renderer);
		SDL_DestroyWindow(state.window);
		delete &state;
	}

	return;
}
