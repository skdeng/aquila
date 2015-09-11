#include "Shape.h"

Primitive::Primitive()
{

}

Primitive::~Primitive()
{

}

Triangle::Triangle()
{

}

Triangle::Triangle(const vec3& aA, const vec3& aB, const vec3& aC, const vec3& aColor)
{
	mA = aA;
	mB = aB;
	mC = aC;
	mColor = aColor;

	mAB = aB - aA;
	mAC = aC - aA;
	mBC = aC - aB;

	mNormal = cross(mAC, mAB);
	mNormal = normalize(mNormal);
}

bool Triangle::Intersect(const Ray& aRay, float* aT, LocalGeo* aGeometry)
{
	const vec3& RayOrigin = aRay.Pos;
	const vec3& RayDir = aRay.Dir;

	//check if ray is parallel to the plane
	//I consider tangent as non-intersecting
	float theta = dot(RayDir, mNormal);
	if (theta == 0)
		return false;

	//calculate intersection
	float tmpT = (dot(mA, mNormal) - dot(RayOrigin, mNormal)) / theta;

	//check boundaries
	if (tmpT < aRay.TMin || tmpT > aRay.TMax)
		return false;

	vec3 IntersectionPoint = RayOrigin + tmpT * RayDir;

	//check if the intersection point with the plane is inside the triangle
	if (!Inside(IntersectionPoint))
		return false;

	if (!aT)
	{
		*aT = tmpT;
	}
	if (!aGeometry)
	{
		aGeometry->Pos = IntersectionPoint;
		aGeometry->Normal = mNormal;
	}

	return true;
}

bool Triangle::Inside(const vec3& aPoint)
{

}

bool Triangle::Inside(const float afX, const float afY, const float afZ)
{
	
}

Sphere::Sphere()
{

}

Sphere::Sphere(const vec3& aCenter, const float aRadius)
{
	mCenter = aCenter;
	mRadius = aRadius;
}

Sphere::~Sphere()
{

}

bool Sphere::Intersect(const Ray& aRay, float* aT = nullptr, LocalGeo* aGeometry = nullptr)
{
	//TODO
	return true;
}