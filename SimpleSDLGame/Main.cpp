#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <chrono>
#include <vector>

#include "Vectors.h"
#include "Rect.h"
#include "Player.h"
#include "EntityManager.h"
#include "Utilities.h"

typedef std::chrono::high_resolution_clock Clock;
using std::vector;

Vector2 XY = Vector2();

bool bIsDashing;
bool bDashReady;
float dashDistance;
float dashTimeRemaining = 0.0f;
Vector2 lastDash = Vector2();

Player* player = new Player();

//EntityManager* entityManager = new EntityManager();

//TODO remove for entity based system
vector<Rect*> Spawnables;

void SpawnRect(Vector2 spawnLocation)
{
    float size = 20.0f;

    Rect* newRect = new Rect(spawnLocation.X, spawnLocation.Y, size, size);
    Spawnables.push_back(newRect);
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

        //Print number of entities
        auto n = EntityManager::GetEntities().size();
        printf("%zd \n", n);

        vector<Entity*> Entities = EntityManager::GetEntities();
        for (Entity* Entity : Entities)
        {
            if (!Entity->bIsPendingDestroy)
            {
                Entity->Update(delta);
                Entity->Render(renderer);
            }
        }

        player->Update(delta);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);

        SDL_FRect localPlayer{};
        localPlayer = Utilities::ConvertRect(player->playerRect);

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

