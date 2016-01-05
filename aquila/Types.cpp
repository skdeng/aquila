#include "Types.h"
#include "Ray.h"

Transformation::Transformation()
{
	mM = MATRIX::I;
	mMinv = MATRIX::I;
}

Transformation::Transformation(const mat4x4& aM)
{
	mM = aM;
	mMinv = inverse(aM);
}

vec4 operator*(const Transformation& aM, const vec4& aV)
{
	return aM.mM * aV;
}

vec3 operator*(const Transformation& aM, const vec3& aV)
{
	vec4 v4 = aM.mM * vec4(aV, 0);
	return vec3(v4.x, v4.y, v4.z);
}

Ray operator*(const Transformation& aM, const Ray& aRay)
{
	return Ray(aM * aRay.Pos, aM * aRay.Dir);
}