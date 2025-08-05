#include "Rect.h"

void Rect::SetRectLocation(Vector2 newLocation)
{
	rect.x = newLocation.X;
	rect.y = newLocation.Y;
}

void Rect::SetRectSize(Vector2 newSize)
{
	rect.w = newSize.X;
	rect.h = newSize.Y;
}
