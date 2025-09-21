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

void Rect::SetRectSizeCenter(Vector2 newSize)
{
	Vector2 oldSize = Vector2(W, H);
	SetRectSize(newSize);
	Vector2 dif = oldSize * 0.5f - newSize * 0.5f;
	SetRectLocation(GetRectLocation() + dif);
}

Vector2 Rect::GetRectLocation()
{
	return Vector2(X, Y);
}
