#pragma once
#include <SDL3/SDL_rect.h>
#include "Rect.h"

class Utilities
{
public:
	Utilities();

	static SDL_FRect ConvertRect(Rect rect);

	static Vector2_int GetScreenBounds();

	void Test();
};

