#include "Utilities.h"

SDL_FRect Utilities::ConvertRect(Rect rect)
{
    SDL_FRect outputRect;
    outputRect.x = rect.X;
    outputRect.y = rect.Y;
    outputRect.w = rect.W;
    outputRect.h = rect.H;
    return outputRect;    
}
