#pragma once

#include "Vectors.h"

class Rect
{
public:

	Rect() = default;
	~Rect() = default;

	float X = 0.0f;
	float Y = 0.0f;
	float W = 0.0f;
	float H = 0.0f;

	Rect(float x, float y, float w, float h)
	{
		X = x;
		Y = y;
		W = w;
		H = h;
	}

	void SetRectLocation(Vector2 newLocation);
	void SetRectSize(Vector2 newSize);
	void SetRectSizeCenter(Vector2 newSize);
	
	Vector2 GetRectLocation();
};

