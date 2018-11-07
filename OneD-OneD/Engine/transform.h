#pragma once

#include "vector2D.h"
#include "vector3D.h"
#include "matrix33.h"

struct Transform
{
	Vector2D position = Vector2D::zero;
	float rotation = 0.0f;
	Vector2D scale = Vector2D::one;
	Matrix33 matrix;

	Transform() {}
	Transform(const Vector2D& position, float rotation = 0.0f, Vector2D scale = Vector2D::one) :
		position(position), 
		rotation(rotation), 
		scale(scale)
		{}

	void Update();
};
