#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

static int keyDownUpdate(SDL_Event event, float& X, float& Y)
{
    switch (event.key.key)
    {
    case SDLK_UP:
        Y = -1;
        break;
    case SDLK_DOWN:
        Y = 1;
        break;
    case SDLK_LEFT:
        X = -1;
        break;
    case SDLK_RIGHT:
        X = 1;
        break;

    default:
        X = 0;
        Y = 0;
        break;
    }

    return 0;
}

int main(int argc, char* argv[])
{
    SDL_Window* window;                     // Declare a pointer
    static SDL_Renderer* renderer = NULL;

    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL3 window",                  // window title
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    renderer = SDL_CreateRenderer(window, NULL);

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    

    float InputX = 0;
    float InputY = 0;

    float rectX = 0;
    float rectY = 0;

    float speed = 100;

    //Calculate delta
    Clock::time_point prevTime;
    float delta;

    while (!done) {

        auto currentTime = Clock::now();
        delta = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - prevTime).count();
        delta = delta / 1e+9;
        prevTime = currentTime;

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }

            float X = 0;
            float Y = 0;

            switch (event.type)
            {
            case SDL_EVENT_KEY_DOWN:
                //printf("Key press detected\n");

                keyDownUpdate(event, X, Y);
                
                InputX += X * delta;
                InputY += Y * delta;
                
                break;

            case SDL_EVENT_KEY_UP:
                //printf("Key release detected\n");
                break;

            default:
                break;
            }

        }

        // Do game logic, present a frame, etc.

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE_FLOAT);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);

        SDL_FRect rect{};

        rect.x = 10 + InputX * speed;
        rect.y = 400 + InputY * speed;
        rect.w = 100;
        rect.h = 100;

        SDL_RenderRect(renderer, &rect);

        SDL_RenderPresent(renderer);

        //printf("%f\n", rect.y);
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);
    //Close and destroy renderer
    SDL_DestroyRenderer(renderer);

    // Clean up
    SDL_Quit();
    return 0;
}

