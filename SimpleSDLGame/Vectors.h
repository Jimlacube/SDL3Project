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

};

using Vector2 = Vector2_base<float>;
using Vector2_double = Vector2_base<double>;
using Vector2_int = Vector2_base<int>;

template <typename T>
inline Vector2_base<T>& operator +=(Vector2_base<T>& a, const Vector2_base<T>& b)
{
	a.X += b.X;
	a.Y += b.Y;
	return a;
};

template <typename T>
inline Vector2_base<T>& operator -=(Vector2_base<T>& a, const Vector2_base<T>& b)
{
	a.X -= b.X;
	a.Y -= b.Y;
	return a;
};

template <typename T>
inline Vector2_base<T>& operator *=(Vector2_base<T>& a, const Vector2_base<T>& b)
{
	a.X *= b.X;
	a.Y *= b.Y;
	return a;
};

template <typename T>
inline Vector2_base<T>& operator /=(Vector2_base<T>& a, const Vector2_base<T>& b)
{
	a.X /= b.X;
	a.Y /= b.Y;
	return a;
};

template <typename T>
inline Vector2_base<T> operator+(const Vector2_base<T>& a, const Vector2_base<T>& b)
{
	return a += b;
}

template <typename T>
inline Vector2_base<T> operator-(const Vector2_base<T>& a, const Vector2_base<T>& b)
{
	return a -= b;
}

template <typename T>
inline Vector2_base<T> operator*(const Vector2_base<T>& a, const Vector2_base<T>& b)
{
	Vector2 c;
	c.X = a.X * b.X;
	c.Y = a.Y * b.Y;
	return c;
}

template <typename T>
inline Vector2_base<T> operator*(Vector2_base<T>& a, const float b)
{
	a.X *= b;
	a.Y *= b;
	return a;
}

template <typename T>
inline Vector2_base<T> operator/(const Vector2_base<T>& a, const Vector2_base<T>& b)
{
	return a /= b;
}
