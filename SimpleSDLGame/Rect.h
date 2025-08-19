#pragma once

#include <SDL3/SDL_rect.h>

#include "Vectors.h"

class Rect
{
public:

	Rect() = default;
	~Rect() = default;

	SDL_FRect rect{};

	Rect(float x, float y, float w, float h)
	{
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
	}

	void SetRectLocation(Vector2 newLocation);
	void SetRectSize(Vector2 newSize);

	Vector2 GetRectLocation();
};

