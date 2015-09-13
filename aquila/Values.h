#ifndef _AQUILA_VALUES_H_
#define _AQUILA_VALUES_H_

#include <limits>
#include "Types.h"

namespace CONSTANT
{
	const int IMAGE_WIDTH = 64;
	const int IMAGE_HEIGHT = 64;

	const float SCENE_MAX_DEPTH = 1000.0f;

	const float RAY_MINIMUM = 0.01f;
	const float RAY_MAXIMUM = std::numeric_limits<float>::infinity();
}

namespace COLOR
{
	static const Color BLACK(0.0f, 0.0f, 0.0f);
	static const Color WHITE(1.0f, 1.0f, 1.0f);
}

#endif