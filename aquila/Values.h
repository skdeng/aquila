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
	static const BRDF SILVER(
		COLOR::SILVER,
		COLOR::SILVER, 
		0.5 * COLOR::WHITE, 
		16,
		0,
		1);
	static const BRDF BLUE_MATT(
		1.0 * COLOR::BLUE, 
		0.4 * COLOR::BLUE, 
		COLOR::BLACK, 
		12,
		0,
		1);
	static const BRDF GOLD(
		COLOR::GOLD, 
		0.5 * COLOR::WHITE, 
		0.2 * COLOR::WHITE,
		16,
		0,
		1);
	static const BRDF GLASS(
		COLOR::SILVER,
		COLOR::SILVER,
		0.3 * COLOR::SILVER,
		18,
		0.8,
		1.5
		);
	static const BRDF MIRROR(
		COLOR::SILVER,
		COLOR::SILVER,
		COLOR::WHITE,
		18,
		0,
		1
		);
}

#endif