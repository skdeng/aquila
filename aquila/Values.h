#ifndef _AQUILA_VALUES_H_
#define _AQUILA_VALUES_H_

#include <limits>
#include "Types.h"

namespace CONSTANT
{
	const aq_float RAY_MINIMUM = 0.0000001f;
	const aq_float RAY_MAXIMUM = 100000;

	static const char* WINDOW_NAME = "Project Aquila - CPU Ray Tracer";

	const aq_float PLANE_HORIZON = 0.01f;
}

namespace COLOR
{
	static const Color BLACK(0.0, 0.0, 0.0);
	static const Color WHITE(1.0, 1.0, 1.0);
	static const Color RED(1.0, 0.0, 0.0);
	static const Color GREEN(0.0, 1.0, 0.0);
	static const Color BLUE(0.0, 0.0, 1.0);
	static const Color GOLD(0.72, 0.45, 0.2);
	static const Color SILVER(0.75, 0.75, 0.75);
}

namespace MATRIX
{
	static const mat4x4 I;
}

namespace MATERIAL
{
	static const Material WHITESTONE(new Lambertian(COLOR::WHITE));
	static const Material BLACKSTONE(new Lambertian(COLOR::WHITE * 0.1));
}

#endif