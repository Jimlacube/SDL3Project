#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <chrono>
#include <vector>

#include "Enemy.h"
#include "Player.h"
#include "EntityManager.h"
#include "Utilities.h"

typedef std::chrono::high_resolution_clock Clock;
using std::vector;

int main(int argc, char* argv[])
{    
    SDL_Window* window = nullptr;
    static SDL_Renderer* renderer = nullptr;

    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3

    // Create an application window with the following settings:

    window = SDL_CreateWindow(
        "An SDL3 window",
        Utilities::GetScreenBounds().X,
        Utilities::GetScreenBounds().Y,
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

    //Create player
    Player* player = EntityManager::Create<Player>();

    //Create Enemy
    Enemy* enemy = EntityManager::Create<Enemy>();
    
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

        //Entity update
        vector<Entity*> Entities = EntityManager::GetEntities();
        for (Entity* Entity : Entities)
        {
            if (!Entity->bIsPendingDestroy)
            {
                Entity->Update(delta);
            }
        }
        //Entity render
        for (Entity* Entity : Entities)
        {
            if (!Entity->bIsPendingDestroy)
            {
                Entity->Render(*renderer);
            }
        }      

        SDL_RenderPresent(renderer);

        EntityManager::CheckForPendingDestroy();
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);
    //Close and destroy renderer
    SDL_DestroyRenderer(renderer);

    // Clean up
    SDL_Quit();
    return 0;
}

