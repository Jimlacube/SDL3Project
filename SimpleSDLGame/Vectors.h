#pragma once

template <typename T>

struct Vector2_base
{
public:
	T X = 0;
	T Y = 0;

	Vector2_base() = default;
	~Vector2_base() = default;

	inline Vector2_base(T x, T y)
	{
		X = x;
		Y = y;
	}

	inline Vector2_base(T xy)
	{
		X = xy;
		Y = xy;
	}
	
	inline Vector2_base<T> operator +=(Vector2_base<T> b)
	{
		X = X + b.X;
		Y = Y + b.Y;
		return Vector2_base<T>(X, Y);
	}
	inline Vector2_base<T> operator -=(Vector2_base<T> b)
	{
		X = X - b.X;
		Y = Y - b.Y;
		return Vector2_base<T>(X, Y);
	}
	inline Vector2_base<T> operator *=(Vector2_base<T> b)
	{
		X = X * b.X;
		Y = Y * b.Y;
		return Vector2_base<T>(X, Y);
	}
	inline Vector2_base<T> operator /=(Vector2_base<T> b)
	{
		X = X / b.X;
		Y = Y / b.Y;
		return Vector2_base<T>(X, Y);
	}
};

using Vector2 = Vector2_base<float>;
using Vector2_double = Vector2_base<double>;
using Vector2_int = Vector2_base<int>;

template <typename T>
inline Vector2_base<T> operator+(const Vector2_base<T>& a, const Vector2_base<T>& b)
{
	return Vector2_base<T>{ a } += b;
}

template <typename T>
inline Vector2_base<T> operator-(const Vector2_base<T>& a, const Vector2_base<T>& b)
{
	return Vector2_base<T>{ a } -= b;
}

template <typename T>
inline Vector2_base<T> operator*(const Vector2_base<T>& a, const Vector2_base<T>& b)
{
	return Vector2_base<T>{ a } *= b;
}

template <typename T>
inline Vector2_base<T> operator*(const Vector2_base<T>& a, const float b)
{
	return Vector2_base<T>(a.X * b, a.Y * b);
}

template <typename T>
inline Vector2_base<T> operator/(const Vector2_base<T>& a, const Vector2_base<T>& b)
{
	return Vector2_base<T>{ a } /= b;
}
