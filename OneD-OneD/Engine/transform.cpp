#include "transform.h"

void Transform::Update()
{
	Matrix33 mxs; mxs.Scale(scale);
	Matrix33 mxr; mxr.Rotate(rotation * Math::DegreesToRadians);
	Matrix33 mxt; mxt.Translate(position);

	matrix = mxs * mxr * mxt;
}

