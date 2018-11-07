#pragma once

#include "_math.h"
#include <assert.h>

class ENGINE_API Vector2D
{
public:
	float x, y;

public:
	Vector2D() {}
	Vector2D(float x, float y) : x(x), y(y) {}
	Vector2D(int x, int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}
	Vector2D(const SDL_Point& point) : x(static_cast<float>(point.x)), y(static_cast<float>(point.y)) {}
	Vector2D& operator = (const Vector2D & v) { x = v.x; y = v.y; return *this; }
	
	float& operator [] (size_t index) {	assert(index <= 1);	return ((&x)[index]); }
	const float& operator [] (size_t index) const { assert(index <= 1);	return ((&x)[index]); }

	bool operator == (const Vector2D & v) const { return Math::IsZero(x - v.x) && Math::IsZero(y - v.y); }
	bool operator != (const Vector2D & v) const { return !(*this == v); }
	bool operator <  (const Vector2D & v) const { return (x < v.x) || ((x == v.x) && (y < v.y)); }
	bool operator >  (const Vector2D & v) const { return !(*this < v) && !(*this == v); }

	Vector2D& operator += (const Vector2D & v) { x += v.x; y += v.y; return *this; }
	Vector2D& operator -= (const Vector2D & v) { x -= v.x; y -= v.y; return *this; }
	Vector2D& operator *= (const Vector2D & v) { x *= v.x; y *= v.y; return *this; }
	Vector2D& operator /= (const Vector2D & v) { x /= v.x; y /= v.y; return *this; }

	const Vector2D operator + (const Vector2D & v) const { Vector2D r(*this); return r += v; }
	const Vector2D operator - (const Vector2D & v) const { Vector2D r(*this); return r -= v; }
	const Vector2D operator * (const Vector2D & v) const { Vector2D r(*this); return r *= v; }
	const Vector2D operator / (const Vector2D & v) const { Vector2D r(*this); return r /= v; }

	Vector2D& operator += (float s) { x += s; y += s; return *this; }
	Vector2D& operator -= (float s) { x -= s; y -= s; return *this; }
	Vector2D& operator *= (float s) { x *= s; y *= s; return *this; }
	Vector2D& operator /= (float s) { x /= s; y /= s; return *this; }

	const Vector2D operator + (float s) const { Vector2D r(*this); return r += s; }
	const Vector2D operator - (float s) const { Vector2D r(*this); return r -= s; }
	const Vector2D operator * (float s) const { Vector2D r(*this); return r *= s; }
	const Vector2D operator / (float s) const { Vector2D r(*this); return r /= s; }

	Vector2D& operator - (void) { x = -x; y = -y; return *this; }

	operator SDL_Point() const
	{
		return { static_cast<int>(x), static_cast<int>(y) };
	}

	static const Vector2D zero;
	static const Vector2D one;
	static const Vector2D up;
	static const Vector2D down;
	static const Vector2D left;
	static const Vector2D right;

	float LengthSquared() const;
	float Length() const;

	const Vector2D& Normalize();
	Vector2D Normalized() const;

	static float LengthSquared(const Vector2D& v1, const Vector2D& v2);
	static float Length(const Vector2D& v1, const Vector2D& v2);
	static float Dot(const Vector2D& v1, const Vector2D& v2);
	static Vector2D Min(const Vector2D& v1, const Vector2D& v2);
	static Vector2D Max(const Vector2D& v1, const Vector2D& v2);
	static Vector2D Rotate(const Vector2D& v1, float angle);
	static float GetAngle(const Vector2D& v);
	static Vector2D GetRandomUnitCircle();
	
	//friend std::ostream & operator << (std::ostream & stream, const Vector2D & v) { stream << "{" << v.x << ", " << v.y << "}"; return stream; }
	//friend std::istream & operator >> (std::istream & stream, Vector2D & v);
};


