#ifndef _AQUILA_RAY_H_
#define _AQUILA_RAY_H_

#include "Types.h"
#include "Values.h"

//! Ray defined as Origin + t * Direction for TMin <= t < TMax
struct Ray
{
	vec3 Pos;
	vec3 Dir;
	float TMax, TMin;

	Ray()
	{

	}

	Ray(vec3 aPos, vec3 aDir, float aTMax = CONSTANT::RAY_MAXIMUM, float aTMin = CONSTANT::RAY_MINIMUM)
	{
		Pos = aPos;
		Dir = aDir;
		TMax = aTMax;
		TMin = aTMin;
	}
};

#endif