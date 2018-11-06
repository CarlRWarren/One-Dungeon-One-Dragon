#pragma once

#include "engine.h"

namespace  Math
{
	constexpr float PI = 3.1415f;
	constexpr float TwoPI = PI * 2.0f;
	constexpr float HalfPI = PI * 0.5f;

	constexpr float DegreesToRadians = PI / 180;
	constexpr float RadiansToDegrees = 180 / PI;

#ifdef __cplusplus
	extern "C"
	{
#endif
		ENGINE_API float Clamp(float v, float low, float high);
		ENGINE_API float Clamp01(float v);
		ENGINE_API float GetRandom01();
		ENGINE_API float GetRandomRange(float min, float max);
		ENGINE_API float Lerp(float v1, float v2, float t);
		ENGINE_API float LerpUnclamped(float v1, float v2, float t);
		ENGINE_API float LerpDegrees(float v1, float v2, float t);
		ENGINE_API bool IsZero(float value);
#ifdef __cplusplus
	}
#endif
}

