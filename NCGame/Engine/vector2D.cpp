#include "vector2D.h"

#include <cassert>
#include <iostream>
#include <string>

const Vector2D Vector2D::zero	= Vector2D( 0.0f,  0.0f);
const Vector2D Vector2D::one	= Vector2D( 1.0f,  1.0f);
const Vector2D Vector2D::up		= Vector2D( 0.0f,  1.0f);
const Vector2D Vector2D::down	= Vector2D( 0.0f, -1.0f);
const Vector2D Vector2D::left	= Vector2D(-1.0f,  0.0f);
const Vector2D Vector2D::right	= Vector2D( 1.0f,  0.0f);

//std::istream & operator >> (std::istream & stream, Vector2D & v)
//{
//	std::string line;
//	std::getline(stream, line);
//
//	if (line.find("{") != std::string::npos)
//	{
//		std::string vx = line.substr(line.find("{") + 1, (line.find(",") - line.find("{")) - 1);
//		v.x = stof(vx);
//		std::string vy = line.substr(line.find(",") + 1, (line.find("}") - line.find(",")) - 1);
//		v.y = stof(vy);
//	}
//
//	return stream;
//}


float Vector2D::LengthSquared() const
{
	return (x * x) + (y * y);
}

float Vector2D::Length() const
{
	return sqrt(LengthSquared());
}

const Vector2D& Vector2D::Normalize()
{
	float length = Length();
	if (Math::IsZero(length))
	{
		x = 0;
		y = 0;
		return *this;
	}
	else
	{
		*this /= length;
		return *this;
	}
}

Vector2D Vector2D::Normalized() const
{
	float length = Length();
	if (Math::IsZero(length))
	{
		return Vector2D(0.0f, 0.0f);
	}
	else
	{
		return *this / length;
	}
}

 float Vector2D::LengthSquared(const Vector2D& v1, const Vector2D& v2)
{
	return ((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y));
}

 float Vector2D::Length(const Vector2D& v1, const Vector2D& v2)
{
	return sqrt(LengthSquared(v1, v2));
}

 float Vector2D::Dot(const Vector2D& v1, const Vector2D& v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}

 Vector2D Vector2D::Min(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y);
}

 Vector2D Vector2D::Max(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D(v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y);
}

 Vector2D Vector2D::Rotate(const Vector2D& v1, float angle)
{
	float x = v1.x * cos(angle) - v1.y * sin(angle);
	float y = v1.x * sin(angle) + v1.y * cos(angle);

	return Vector2D(x, y);
}

 float Vector2D::GetAngle(const Vector2D& v)
{
	return atan2(v.y, v.x);
}

 Vector2D Vector2D::GetRandomUnitCircle()
{
	return Rotate(Vector2D::up, Math::GetRandomRange(0.0f, Math::TwoPI));
}