#include "Rect.h"

void Rect::SetRectLocation(Vector2 newLocation)
{
	X = newLocation.X;
	Y = newLocation.Y;
}

void Rect::SetRectSize(Vector2 newSize)
{
	W = newSize.X;
	H = newSize.Y;
}

Vector2 Rect::GetRectLocation()
{
	return Vector2(X, Y);
}
