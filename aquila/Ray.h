#ifndef _AQUILA_RAY_H_
#define _AQUILA_RAY_H_

#include "Types.h"
#include "Values.h"

//! Ray defined as Origin + t * Direction for TMin <= t < TMax
struct Ray
{
	vec3 Pos;
	vec3 Dir;
	aq_float TMax, TMin;

	Ray()
	{

	}

	Ray(vec3 aPos, vec3 aDir, aq_float aTMax = CONSTANT::RAY_MAXIMUM, aq_float aTMin = CONSTANT::RAY_MINIMUM)
	{
		Pos = aPos;
		Dir = aDir;
		TMax = aTMax;
		TMin = aTMin;
	}

	friend vec3 operator+(Ray r, aq_float t)
	{
		return r.Pos + t * r.Dir;
	}
};

#endif