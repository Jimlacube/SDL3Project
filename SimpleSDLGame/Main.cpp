#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <chrono>
#include "Vectors.h"

typedef std::chrono::high_resolution_clock Clock;

Vector2 XY = Vector2(0.0f);

bool bIsDashing;
bool bDashReady;
float dashDistance;
float dashTimeRemaining = 0.0f;
Vector2 lastDash;

static void StartDash()
{
    if (bDashReady)
    {
        if (!bIsDashing)
        {
            lastDash = XY;

            dashDistance = 100.0f;
            bDashReady = false;
            bIsDashing = true;
        }
    }
}

static float UpdateDashSpeed(float delta ,float timeToComplete = 0.3f)
{
    float dSpeed;
    if (bIsDashing)
    {
        dashTimeRemaining -= delta;  
        const float deltaDashDistance = dashDistance * delta;

        dSpeed = deltaDashDistance / timeToComplete;

        if (dashTimeRemaining <= 0.0f)
        {
            bIsDashing = false;
        }
        return dSpeed;
    }
    else
    {
        dashTimeRemaining = timeToComplete;
        return dSpeed = 1.0f;
    }
}

static void KeyStateUpdate()
{
    const bool* currentKeyStates = SDL_GetKeyboardState(nullptr);
    
    XY = Vector2(0.0f);
    
    if (currentKeyStates[SDL_SCANCODE_UP])      XY.Y -= 1.0f;
    if (currentKeyStates[SDL_SCANCODE_DOWN])    XY.Y += 1.0f;
    if (currentKeyStates[SDL_SCANCODE_LEFT])    XY.X -= 1.0f;
    if (currentKeyStates[SDL_SCANCODE_RIGHT])   XY.X += 1.0f;
    
    //Trigger dash when pressed. Reset dash when the key is released
    if (currentKeyStates[SDL_SCANCODE_SPACE])
    {
        StartDash();
    }
    else
    {
        bDashReady = true;
    }
}

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    static SDL_Renderer* renderer = nullptr;

    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL3 window",
        640,
        480,
        SDL_WINDOW_OPENGL
    );

    renderer = SDL_CreateRenderer(window, nullptr);
    SDL_SetRenderVSync(renderer, 1);

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    Vector2 position = Vector2(200.0f, 200.0f);

    float speed = 100.0f;

    float dashSpeed = 1.0f;

    float rectSize = 20.0f;

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
            if (event.type == SDL_EVENT_QUIT) 
                done = true;
        }

        KeyStateUpdate();
        
        //Setup rendering 
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 1);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);

        dashSpeed = UpdateDashSpeed(delta);

        if (bIsDashing)
        {
            XY = lastDash;
        }

        position += XY * Vector2(dashSpeed * speed * delta);

        SDL_FRect rect{};

        rect.x = position.X;
        rect.y = position.Y;
        rect.w = rectSize;
        rect.h = rectSize;

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

