#ifndef _AQUILA_VALUES_H_
#define _AQUILA_VALUES_H_

#include <limits>
#include "Types.h"

namespace CONSTANT
{
	const float RAY_MINIMUM = 0.00001f;
	const float RAY_MAXIMUM = 100000;

	static const char* WINDOW_NAME = "Project Aquila - CPU Ray Tracer";

	const float PLANE_HORIZON = 0.001f;
}

namespace COLOR
{
	static const Color BLACK(0.0f, 0.0f, 0.0f);
	static const Color WHITE(1.0f, 1.0f, 1.0f);
	static const Color RED(1.0f, 0.0f, 0.0f);
	static const Color GREEN(0.0f, 1.0f, 0.0f);
	static const Color BLUE(0.0f, 0.0f, 1.0f);
}

namespace MATRIX
{
	static const mat4x4 I;
}

namespace MATERIAL
{
	static const BRDF SILVER(0.8f * COLOR::WHITE, 0.6f * COLOR::WHITE, 0.1f * COLOR::WHITE, COLOR::WHITE, 56);
	static const BRDF BLUE_MATT(1.0f * COLOR::BLUE, 0.4f * COLOR::BLUE, 0.1f * COLOR::BLUE, COLOR::BLUE, 12);
}

#endif