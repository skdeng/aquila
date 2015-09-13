#ifndef _AQUILA_SHAPE_H_
#define _AQUILA_SHAPE_H_

#include "Common.h"

//! Abstract class for all primitives
class Primitive
{
public:
	Primitive();
	virtual ~Primitive();

	virtual bool Intersect(const Ray& aRay, float* aT, Intersection* aIntersection) = 0;
	virtual void GetBRDF(const LocalGeo& aLocal, BRDF* aBRDF) = 0;

protected:
	//TODO use material for texture
	BRDF mMaterial;
};

//! Triangles, derived from Primitive
class Triangle : public Primitive
{
public:
	Triangle();
	Triangle(const vec3& aA, const vec3& aB, const vec3& aC, const Color& aColor);
	~Triangle();

	bool Intersect(const Ray& aRay, float* aT = nullptr, Intersection* aIntersection = nullptr);
	void GetBRDF(const LocalGeo& aLocal, BRDF* aBRDF);

private:
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

	bool Intersect(const Ray& aRay, float* aT = nullptr, Intersection* aIntersection = nullptr);

private:
	vec3 mCenter;
	float mRadius;
};

#endif