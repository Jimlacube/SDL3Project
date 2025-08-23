#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <chrono>
#include <vector>

#include "Vectors.h"
#include "Rect.h"

typedef std::chrono::high_resolution_clock Clock;
using std::vector;

Vector2 XY = Vector2();

bool bIsDashing;
bool bDashReady;
float dashDistance;
float dashTimeRemaining = 0.0f;
Vector2 lastDash = Vector2();

Rect player = Rect();

vector<Rect*> Spawnables;

SDL_FRect ConvertRect(Rect rect)
{
    SDL_FRect outputRect;
    outputRect.x = rect.X;
    outputRect.y = rect.Y;
    outputRect.w = rect.W;
    outputRect.h = rect.H;
    return outputRect;
}

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

void SpawnRect(Vector2 spawnLocation)
{
    float size = 20.0f;

    Rect* newRect = new Rect(spawnLocation.X, spawnLocation.Y, size, size);
    Spawnables.push_back(newRect);
}

static void KeyStateUpdate()
{
    const bool* currentKeyStates = SDL_GetKeyboardState(nullptr);
    
    XY = Vector2();
    
    if (currentKeyStates[SDL_SCANCODE_UP])      XY.Y -= 1.0f;
    if (currentKeyStates[SDL_SCANCODE_DOWN])    XY.Y += 1.0f;
    if (currentKeyStates[SDL_SCANCODE_LEFT])    XY.X -= 1.0f;
    if (currentKeyStates[SDL_SCANCODE_RIGHT])   XY.X += 1.0f;
    
    //Trigger dash when pressed. Reset dash when the key is released
    if (currentKeyStates[SDL_SCANCODE_SPACE])
    {
        StartDash();

        SpawnRect(player.GetRectLocation());
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
    int screenWidth = 640;
    int screenHeight = 480;

    window = SDL_CreateWindow(
        "An SDL3 window",
        screenWidth,
        screenHeight,
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
        
        //Setup rendering 
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 1);
        SDL_RenderClear(renderer);
        
        KeyStateUpdate();

        dashSpeed = UpdateDashSpeed(delta);

        if (bIsDashing)
        {
            XY = lastDash;
        }

        for (int i = 0; i < Spawnables.size(); ++i)
        {
            Rect* rect = Spawnables[i];

            if (rect != nullptr)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
                SDL_RenderRect(renderer, (const SDL_FRect*)rect);

                Vector2 rectLocation = rect->GetRectLocation();
                rect->SetRectLocation(Vector2(rectLocation.X, rectLocation.Y + 5.0f));

                //Delete rects when they go off screen
                if (rect->GetRectLocation().Y > screenHeight + 20.0f)
                {
                    delete rect;
                    rect = nullptr;
                    Spawnables[i] = Spawnables[Spawnables.size() - 1];
                    Spawnables.pop_back();
                    --i;
                }
            }
        }

        position += XY * (dashSpeed * speed * delta);        

        player.SetRectLocation(position);
        player.SetRectSize(rectSize);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);

        SDL_FRect localPlayer{};
        localPlayer = ConvertRect(player);

        SDL_RenderRect(renderer, &localPlayer);

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

