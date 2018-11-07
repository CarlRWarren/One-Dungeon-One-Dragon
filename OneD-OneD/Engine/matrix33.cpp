#include "matrix33.h"

const Matrix33 Matrix33::identity = Matrix33(Vector3D(1.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector3D(0.0f, 0.0f, 1.0f));

void Matrix33::Rotate(float angle)
{
	m[0][0] = static_cast<float>( cos(angle)); m[1][0] = static_cast<float>(sin(angle)); m[2][0] = 0.0f;
	m[0][1] = static_cast<float>(-sin(angle)); m[1][1] = static_cast<float>(cos(angle)); m[2][1] = 0.0f;
	m[0][2] = 0.0f;							   m[1][2] = 0.0f;							 m[2][2] = 1.0f;
}