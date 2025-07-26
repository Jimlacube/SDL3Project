#include "Vectors.h"


Vector2 operator+(const Vector2& a, const Vector2& b)
{
	return Vector2(a.X + b.X, a.Y + b.Y);
}

Vector2 operator-(const Vector2& a, const Vector2& b)
{
	return Vector2(a.X - b.X, a.Y - b.Y);
}

Vector2 operator*(const Vector2& a, const Vector2& b)
{
	return Vector2(a.X * b.X, a.Y * b.Y);
}

Vector2 operator/(const Vector2& a, const Vector2& b)
{
	return Vector2(a.X / b.X, a.Y / b.Y);
}

Vector2& operator +=(Vector2& a, const Vector2& b)
{
	a.X += b.X;
	a.Y += b.Y;
	return a;
};

Vector2& operator -=(Vector2& a, const Vector2& b)
{
	a.X -= b.X;
	a.Y -= b.Y;
	return a;
};

Vector2& operator *=(Vector2& a, const Vector2& b)
{
	a.X *= b.X;
	a.Y *= b.Y;
	return a;
};

Vector2& operator /=(Vector2& a, const Vector2& b)
{
	a.X /= b.X;
	a.Y /= b.Y;
	return a;
};