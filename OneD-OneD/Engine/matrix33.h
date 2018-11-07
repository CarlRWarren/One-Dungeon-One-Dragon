#pragma once

#include "vector2D.h"
#include "vector3D.h"

class ENGINE_API Matrix33
{
public:
	float m[3][3]; // column / row

public:
	Matrix33() {}
	Matrix33(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3)
	{
		m[0][0] = v1[0]; m[1][0] = v2[0]; m[2][0] = v3[0];
		m[0][1] = v1[1]; m[1][1] = v2[1]; m[2][1] = v3[1];
		m[0][2] = v1[2]; m[1][2] = v2[2]; m[2][2] = v3[2];
	}
	~Matrix33() {}

	void SetIdentity()
	{
		m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f;
		m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
	}

	void Scale(float s)
	{
		m[0][0] = s;    m[1][0] = 0.0f; m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = s;	m[2][1] = 0.0f;
		m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
	}

	void Scale(const Vector2D& s)
	{
		m[0][0] = s.x;  m[1][0] = 0.0f; m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = s.y;	m[2][1] = 0.0f;
		m[0][2] = 0.0f; m[1][2] = 0.0f; m[2][2] = 1.0f;
	}

	void Rotate(float angle);

	void Translate(const Vector2D& v)
	{
		m[0][0] = 1.0f; m[1][0] = 0.0f; m[2][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = 1.0f; m[2][1] = 0.0f;
		m[0][2] =  v.x; m[1][2] =  v.y; m[2][2] = 1.0f;
	}

	Matrix33 operator * (const Matrix33& mx) const
	{
		Matrix33 result;

		result.m[0][0] = m[0][0] * mx.m[0][0] + m[1][0] * mx.m[0][1] + m[2][0] * mx.m[0][2];
		result.m[0][1] = m[0][1] * mx.m[0][0] + m[1][1] * mx.m[0][1] + m[2][1] * mx.m[0][2];
		result.m[0][2] = m[0][2] * mx.m[0][0] + m[1][2] * mx.m[0][1] + m[2][2] * mx.m[0][2];

		result.m[1][0] = m[0][0] * mx.m[1][0] + m[1][0] * mx.m[1][1] + m[2][0] * mx.m[1][2];
		result.m[1][1] = m[0][1] * mx.m[1][0] + m[1][1] * mx.m[1][1] + m[2][1] * mx.m[1][2];
		result.m[1][2] = m[0][2] * mx.m[1][0] + m[1][2] * mx.m[1][1] + m[2][2] * mx.m[1][2];

		result.m[2][0] = m[0][0] * mx.m[2][0] + m[1][0] * mx.m[2][1] + m[2][0] * mx.m[2][2];
		result.m[2][1] = m[0][1] * mx.m[2][0] + m[1][1] * mx.m[2][1] + m[2][1] * mx.m[2][2];
		result.m[2][2] = m[0][2] * mx.m[2][0] + m[1][2] * mx.m[2][1] + m[2][2] * mx.m[2][2];

		return result;
	}

	Vector2D operator * (const Vector2D& v)
	{
		Vector2D result;

		result.x = v.x * m[0][0] + v.y * m[0][1];
		result.y = v.x * m[1][0] + v.y * m[1][1];

		return result;
	}

	friend Vector2D operator * (const Vector2D& v, const Matrix33& mx)
	{
		Vector2D result;

		result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1] + mx.m[0][2];
		result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1] + mx.m[1][2];

		return result;
	}

	friend Vector3D operator * (const Vector3D& v, const Matrix33& mx)
	{
		Vector3D result;

		result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1] + v.z * mx.m[0][2];
		result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1] + v.z * mx.m[1][2];
		result.z = v.x * mx.m[2][0] + v.y * mx.m[2][1] + v.z * mx.m[2][2];

		return result;
	}
		
	static const Matrix33 identity;
};

