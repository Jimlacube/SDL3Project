#pragma once
#include <SDL3/SDL_rect.h>
#include "Rect.h"

class Utilities
{
public:
	Utilities() = default;

	static SDL_FRect ConvertRect(Rect rect);
};

