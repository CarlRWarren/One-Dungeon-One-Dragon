#pragma once
#include "vector2D.h"

struct Variant
{
	enum eType
	{
		INTEGER,
		FLOAT,
		BOOL,
		VECTOR2D
	};
	eType type;

	union {
		int asInteger;
		float asFloat;
		bool asBool;
		Vector2D asVector2D;
	};

	Variant() {}
};