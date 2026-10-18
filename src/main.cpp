#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <new>

struct AppState {
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};

SDL_AppResult SDL_AppInit(void **appstate, int, char **) {
    auto *state = new (std::nothrow) AppState{};
    if (state == nullptr) {
        return SDL_APP_FAILURE;
    }

    *appstate = state;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(
            "Physics", 800, 600, SDL_WINDOW_RESIZABLE,
            &state->window, &state->renderer)) {
        SDL_Log("Failed to create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT ||
        event->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    auto *state = static_cast<AppState *>(appstate);
    SDL_SetRenderDrawColor(state->renderer, 18, 24, 32, 255);
    SDL_RenderClear(state->renderer);
    SDL_RenderPresent(state->renderer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult) {
    auto *state = static_cast<AppState *>(appstate);
    if (state != nullptr) {
        SDL_DestroyRenderer(state->renderer);
        SDL_DestroyWindow(state->window);
        delete state;
    }
    SDL_Quit();
}

