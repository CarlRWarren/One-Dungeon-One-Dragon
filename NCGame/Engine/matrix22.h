#pragma once

#include "vector2D.h"

class ENGINE_API Matrix22
{
public:
	float m[2][2]; // column / row

public:
	Matrix22() {}
	Matrix22(const Vector2D& v1, const Vector2D& v2)
	{
		m[0][0] = v1[0]; m[1][0] = v2[0];
		m[0][1] = v1[1]; m[1][1] = v2[1];
	}
	~Matrix22() {}

	void SetIdentity()
	{
		m[0][0] = 1.0f; m[1][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = 1.0f;
	}

	void Scale(float s)
	{
		m[0][0] = s;    m[1][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = s;
	}

	void Scale(const Vector2D& s)
	{
		m[0][0] = s.x;  m[1][0] = 0.0f;
		m[0][1] = 0.0f; m[1][1] = s.y;
	}

	void Rotate(float angle);

	Matrix22 operator * (const Matrix22& mx)
	{
		Matrix22 result;

		result.m[0][0] = m[0][0] * mx.m[0][0] + m[1][0] * mx.m[0][1];
		result.m[0][1] = m[0][1] * mx.m[0][0] + m[1][1] * mx.m[0][1];
		result.m[1][0] = m[0][0] * mx.m[1][0] + m[1][0] * mx.m[1][1];
		result.m[1][1] = m[0][1] * mx.m[1][0] + m[1][1] * mx.m[1][1];

		return result;
	}

	Vector2D operator * (const Vector2D& v)
	{
		Vector2D result;

		result.x = v.x * m[0][0] + v.y * m[0][1];
		result.y = v.x * m[1][0] + v.y * m[1][1];

		return result;
	}

	friend Vector2D operator * (const Vector2D& v, const Matrix22& mx)
	{
		Vector2D result;

		result.x = v.x * mx.m[0][0] + v.y * mx.m[0][1];
		result.y = v.x * mx.m[1][0] + v.y * mx.m[1][1];

		return result;
	}

	static const Matrix22 identity;
};
