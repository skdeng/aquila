#ifndef _AQUILA_RAY_H_
#define _AQUILA_RAY_H_

#include "glmath.h"

struct Ray
{
	vec3 Pos;
	vec3 Dir;
	float TMax, TMin;

	Ray(vec3 aPos, vec3 aDir, float aTMax = std::numeric_limits<float>::infinity(), float aTMin = 0.0f)
	{
		Pos = aPos;
		Dir = aDir;
		TMax = aTMax;
		TMin = aTMin;
	}
};

#endif