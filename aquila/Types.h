#ifndef _AQUILA_UTILS_TYPE_H_
#define _AQUILA_UTILS_TYPE_H_

#include "glmath.h"
#include "Shape.h"

typedef vec2 Sample;
typedef vec3 Color;

class Transformation
{
public:
	Transformation(const mat4x4& aM);

	friend vec4 operator*(const Transformation& aM, const vec4& aV);
	friend vec3 operator*(const Transformation& aM, const vec3& aV);
private:
	mat4x4 mM, mMinv;
};

//! Local geometry at intersection point
struct LocalGeo
{
	vec3 Pos;
	vec3 Normal;
};

//! Intersection point information in world-space
struct Intersection
{
	LocalGeo Geometry
	Primitive* Object;
};
#endif