#include "vector3D.h"
#include <iostream>
#include <string>
#include <tuple>

const Vector3D Vector3D::zero	= Vector3D( 0.0f,  0.0f, 0.0f);
const Vector3D Vector3D::one	= Vector3D( 1.0f,  1.0f, 0.0f);
const Vector3D Vector3D::up		= Vector3D( 0.0f,  1.0f, 0.0f);
const Vector3D Vector3D::down	= Vector3D( 0.0f, -1.0f, 0.0f);
const Vector3D Vector3D::left	= Vector3D(-1.0f,  0.0f, 0.0f);
const Vector3D Vector3D::right	= Vector3D( 1.0f,  0.0f, 0.0f);

//std::istream & operator >> (std::istream & stream, Vector3D & v)
//{
//	std::string line;
//	std::getline(stream, line);
//
//	if (line.find("{") != std::string::npos)
//	{
//		std::string vx = line.substr(line.find("{") + 1, (line.find(",") - line.find("{")) - 1);
//		v.x = stof(vx);
//		line = line.substr(line.find(",") + 1, (line.find("}") - line.find(",")) - 1);
//		std::string vy = line.substr(0, line.find(",") - 1);
//		v.y = stof(vy);
//		std::string vz = line.substr(line.find(",") + 1, (line.find("}") - line.find(",")) - 1);
//		v.z = stof(vz);
//	}
//
//	return stream;
//}

bool Vector3D::operator != (const Vector3D & v) const 
{ 
	return !(*this == v);
}

bool Vector3D::operator < (const Vector3D & v) const
{ 
	return std::tie(x, y, z) == std::tie(v.x, v.y, v.z);
}

bool Vector3D::operator >  (const Vector3D & v) const 
{ 
	return !(*this < v) && !(*this == v);
}

float Vector3D::LengthSquared() const
{
	return (x * x) + (y * y) + (z * z);
}

float Vector3D::Length() const
{
	return sqrt(LengthSquared());
}

const Vector3D& Vector3D::Normalize()
{
	float length = Length();
	if (Math::IsZero(length))
	{
		x = 0;
		y = 0;
		z = 0;
		return *this;
	}
	else
	{
		*this /= length;
		return *this;
	}
}

Vector3D Vector3D::Normalized() const
{
	float length = Length();
	if (Math::IsZero(length))
	{
		return Vector3D::zero;
	}
	else
	{
		return *this / length;
	}
}

inline float Vector3D::LengthSquared(const Vector3D& v1, const Vector3D& v2)
{
	return (v1 - v2).LengthSquared();
}

inline float Vector3D::Length(const Vector3D& v1, const Vector3D& v2)
{
	return (v1 - v2).Length();
}

inline float Vector3D::Dot(const Vector3D& v1, const Vector3D& v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

inline Vector3D Vector3D::Min(const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.x < v2.x ? v1.x : v2.x, v1.y < v2.y ? v1.y : v2.y, v1.z < v2.z ? v1.z : v2.z);
}

inline Vector3D Vector3D::Max(const Vector3D& v1, const Vector3D& v2)
{
	return Vector3D(v1.x > v2.x ? v1.x : v2.x, v1.y > v2.y ? v1.y : v2.y, v1.z > v2.z ? v1.z : v2.z);
}
