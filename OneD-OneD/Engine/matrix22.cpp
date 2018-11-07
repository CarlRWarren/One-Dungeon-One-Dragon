#include "matrix22.h"

const Matrix22 Matrix22::identity = Matrix22(Vector2D(1.0f, 0.0f), Vector2D(0.0f, 1.0f));

void Matrix22::Rotate(float angle)
{
	m[0][0] = static_cast<float>( cos(angle)); m[1][0] = static_cast<float>(sin(angle));
	m[0][1] = static_cast<float>(-sin(angle)); m[1][1] = static_cast<float>(cos(angle));
}