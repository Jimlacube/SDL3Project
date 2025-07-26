#pragma once

struct Vector2
{
public:
	//Unsure whether to use float or double here
	float X = 0.0f;
	float Y = 0.0f;

	Vector2()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	Vector2(float x, float y)
	{
		X = x;
		Y = y;
	}

	Vector2(float xy)
	{
		X = xy;
		Y = xy;
	}
};

Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& a, const Vector2& b);
Vector2 operator/(const Vector2& a, const Vector2& b);

Vector2& operator +=(Vector2& a, const Vector2& b);
Vector2& operator -=(Vector2& a, const Vector2& b);
Vector2& operator *=(Vector2& a, const Vector2& b);
Vector2& operator /=(Vector2& a, const Vector2& b);