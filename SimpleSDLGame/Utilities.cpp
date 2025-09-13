#include "Utilities.h"
#include "Vectors.h"

Utilities::Utilities()
{
    Test();
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

void Utilities::Test()
{
    Vector2 a = Vector2(2.0f,2.0f);
    Vector2 b = Vector2(2.0f,2.0f);
    Vector2 c = Vector2(2.0f,2.0f);

    c += a;
    c -= a;
    c *= a;
    c /= a;
    c = a + b;
    c = a - b;
    c = a * b;
    c = a / b;
    c = a * 0.5f;
}
