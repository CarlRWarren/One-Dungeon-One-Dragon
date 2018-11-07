#pragma once

#include "_math.h"
#include "vector2D.h"
#include <assert.h>

class ENGINE_API Vector3D
{
public:
	float x, y, z;

public:
	Vector3D() {}
	Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3D(const Vector2D& v, float z) { x = v.x; y = v.y; this->z = z; }
	Vector3D& operator = (const Vector3D & v) { x = v.x; y = v.y; z = v.z; return *this; }

	float& operator [] (size_t index) { assert(index <= 2); return ((&x)[index]); }
	const float& operator [] (size_t index) const { assert(index <= 2); return ((&x)[index]); }

	bool operator == (const Vector3D & v) const { return Math::IsZero(x - v.x) && Math::IsZero(y - v.y) && Math::IsZero(z - v.z); }

	bool operator != (const Vector3D & v) const;
	bool operator <  (const Vector3D & v) const;
	bool operator >  (const Vector3D & v) const;

	Vector3D& operator += (const Vector3D & v) { x += v.x; y += v.y;  z += v.z; return *this; }
	Vector3D& operator -= (const Vector3D & v) { x -= v.x; y -= v.y;  z -= v.z; return *this; }
	Vector3D& operator *= (const Vector3D & v) { x *= v.x; y *= v.y;  z *= v.z; return *this; }
	Vector3D& operator /= (const Vector3D & v) { x /= v.x; y /= v.y;  z /= v.z; return *this; }

	const Vector3D operator + (const Vector3D & v) const { Vector3D r(*this); return r += v; }
	const Vector3D operator - (const Vector3D & v) const { Vector3D r(*this); return r -= v; }
	const Vector3D operator * (const Vector3D & v) const { Vector3D r(*this); return r *= v; }
	const Vector3D operator / (const Vector3D & v) const { Vector3D r(*this); return r /= v; }

	Vector3D& operator += (float s) { x += s; y += s; z += s; return *this; }
	Vector3D& operator -= (float s) { x -= s; y -= s; z -= s; return *this; }
	Vector3D& operator *= (float s) { x *= s; y *= s; z *= s; return *this; }
	Vector3D& operator /= (float s) { x /= s; y /= s; z /= s; return *this; }

	const Vector3D operator + (float s) const { Vector3D r(*this); return r += s; }
	const Vector3D operator - (float s) const { Vector3D r(*this); return r -= s; }
	const Vector3D operator * (float s) const { Vector3D r(*this); return r *= s; }
	const Vector3D operator / (float s) const { Vector3D r(*this); return r /= s; }

	Vector3D& operator - (void) { x = -x; y = -y; z = -z; return *this; }

	operator Vector2D() const
	{
		return (Vector2D(x, y));
	}

	operator SDL_Point() const
	{
		return { static_cast<int>(x), static_cast<int>(y) };
	}

	static const Vector3D zero;
	static const Vector3D one;
	static const Vector3D up;
	static const Vector3D down;
	static const Vector3D left;
	static const Vector3D right;

	float LengthSquared() const;
	float Length() const;
	const Vector3D& Normalize();
	Vector3D Normalized() const;

	inline static float LengthSquared(const Vector3D& v1, const Vector3D& v2);
	inline static float Length(const Vector3D& v1, const Vector3D& v2);
	inline static float Dot(const Vector3D& v1, const Vector3D& v2);
	inline static Vector3D Min(const Vector3D& v1, const Vector3D& v2);
	inline static Vector3D Max(const Vector3D& v1, const Vector3D& v2);

	//friend std::ostream & operator << (std::ostream & stream, const Vector3D & v) { stream << "{" << v.x << ", " << v.y << ", " << v.z << "}"; return stream; }
	//friend std::istream & operator >> (std::istream & stream, Vector3D & v);
};


