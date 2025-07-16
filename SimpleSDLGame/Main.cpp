#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

float X = 0;
float Y = 0;

static void keyStateUpdate()
{
    X = 0;
    Y = 0;

    const bool* currentKeyStates = SDL_GetKeyboardState(nullptr);

    if (currentKeyStates[SDL_SCANCODE_UP])      Y -= 1.0f;
    if (currentKeyStates[SDL_SCANCODE_DOWN])    Y += 1.0f;
    if (currentKeyStates[SDL_SCANCODE_LEFT])    X -= 1.0f;
    if (currentKeyStates[SDL_SCANCODE_RIGHT])   X += 1.0f;
}

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;                     // Declare a pointer
    static SDL_Renderer* renderer = nullptr;

    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL3 window",                  // window title
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    float positionX = 200.0f;
    float positionY = 200.0f;

    float speed = 100.0f;

    //Calculate delta
    Clock::time_point prevTime;
    float delta;

    while (!done) {

        auto currentTime = Clock::now();
        double nanoseconds = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - prevTime).count();
        delta = (float)(nanoseconds * 1e-9);
        prevTime = currentTime;

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) done = true;

            keyStateUpdate();
        }

        // Do game logic, present a frame, etc.

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE_FLOAT);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);

        SDL_FRect rect{};

        positionX += X * speed * delta;
        positionY += Y * speed * delta;

        rect.x = positionX;
        rect.y = positionY;
        rect.w = 100;
        rect.h = 100;

        SDL_RenderRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);
    //Close and destroy renderer
    SDL_DestroyRenderer(renderer);

    // Clean up
    SDL_Quit();
    return 0;
}

