#ifndef _AQUILA_VALUES_H_
#define _AQUILA_VALUES_H_

#include <limits>
#include "Types.h"

namespace CONSTANT
{
	const int IMAGE_WIDTH = 800;
	const int IMAGE_HEIGHT = 600;

	const float SCENE_MAX_DEPTH = 1000.0f;

	const float RAY_MINIMUM = 0.0001f;
	const float RAY_MAXIMUM = std::numeric_limits<float>::infinity();

	static const char* WINDOW_NAME = "Project Aquila - CPU Ray Tracer";
}

namespace COLOR
{
	static const Color BLACK(0.0f, 0.0f, 0.0f);
	static const Color WHITE(1.0f, 1.0f, 1.0f);
	static const Color RED(1.0f, 0.0f, 0.0f);
	static const Color GREEN(0.0f, 1.0f, 0.0f);
	static const Color BLUE(0.0f, 0.0f, 1.0f);
}

#endif