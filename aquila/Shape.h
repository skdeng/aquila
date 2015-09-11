#ifndef _AQUILA_SHAPE_H_
#define _AQUILA_SHAPE_H_

#include "Ray.h"
#include "Types.h"

//! Abstract class for all primitives
class Primitive
{
public:
	Primitive();
	virtual ~Primitive();

	virtual bool Intersect(const Ray& aRay, float* aT, LocalGeo* aGeometry) = 0;
};

//! Triangles, derived from Primitive
class Triangle : public Primitive
{
public:
	Triangle();
	Triangle(const vec3& aA, const vec3& aB, const vec3& aC, const vec3& aColor);
	~Triangle();

	bool Intersect(const Ray& aRay, float* aT = nullptr, LocalGeo* aGeometry = nullptr);

	bool Inside(const float afX, const float afY, const float afZ);
	bool Inside(const vec3& aPoint);

private:
	vec3 mA, mB, mC;
	vec3 mAB, mAC, mBC;
	vec3 mColor;
	vec3 mNormal;	//normal to the plane
};

class Sphere : public Primitive
{
public:
	Sphere();
	Sphere(const vec3& aCenter, const float aRadius);
	~Sphere();

	bool Intersect(const Ray& aRay, float* aT = nullptr, LocalGeo* aGeometry = nullptr);

private:
	vec3 mCenter;
	float mRadius;
};

#endif