#include "Utilities.h"

Utilities::Utilities()
{
}

SDL_FRect Utilities::ConvertRect(Rect rect)
{
    SDL_FRect outputRect;
    outputRect.x = rect.X;
    outputRect.y = rect.Y;
    outputRect.w = rect.W;
    outputRect.h = rect.H;
    return outputRect;    
}

Vector2_int Utilities::GetScreenBounds()
{
    return Vector2_int(640, 480);
}
