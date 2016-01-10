#ifndef _AQUILA_SHAPE_H_
#define _AQUILA_SHAPE_H_

#include "Common.h"
#include "Types.h"

//! Abstract class for all primitives
class Primitive
{
public:
	Primitive();
	virtual ~Primitive();

	virtual bool Intersect(const Ray& aRay, aq_float* aT, Intersection* aIntersection) = 0;
	Primitive* Transform(const Transformation& aM);
	
protected:
	//TODO use material for texture
	Transformation mM;
	BRDF mMaterial;
};

//==================================================================================================

//! Triangles, derived from Primitive
class Triangle : public Primitive
{
public:
	Triangle(const vec3& aA, const vec3& aB, const vec3& aC, const BRDF& aMaterial);
	~Triangle();

	bool Intersect(const Ray& aRay, aq_float* aT, Intersection* aIntersection);

private:
	bool Inside(const aq_float afX, const aq_float afY, const aq_float afZ);
	bool Inside(const vec3& aPoint);

	void Barycentric(const vec3 &aP, vec3* aBP)
	{
		vec3 PA = aP - mA;
		aq_float d00 = dot(mAB, mAB);
		aq_float d01 = dot(mAB, mAC);
		aq_float d11 = dot(mAC, mAC);
		aq_float d20 = dot(PA, mAB);
		aq_float d21 = dot(PA, mAC);
		aq_float denom = d00 * d11 - d01 * d01;
		aBP->y = (d11 * d20 - d01 * d21) / denom;
		aBP->z = (d00 * d21 - d01 * d20) / denom;
		aBP->x = 1.0 - aBP->y - aBP->z;
	}

private:
	vec3 mA, mB, mC;
	vec3 mAB, mAC;
	vec3 mColor;
	vec3 mNormal;	//normal to the plane
};

//=================================================================================================

//! Sphere
/*!
	A sphere defined by its center and radius
*/
class Sphere : public Primitive
{
public:
	Sphere(const vec3& aCenter, const aq_float aRadius, const BRDF& aMaterial);
	~Sphere();

	bool Intersect(const Ray& aRay, aq_float* aT, Intersection* aIntersection);

private:
	vec3 mCenter;
	aq_float mRadius;
};

class Box : public Primitive
{
public:
	Box(const vec3& aMin, const vec3& aMax, const BRDF& aMaterial);
	~Box();

	bool Intersect(const Ray& aRay, aq_float* aT, Intersection* aIntersection);

private:
	vec3 mMin, mMax;
};

//=================================================================================================

class Plane : public Primitive
{
public:
	Plane(const BRDF& aMaterial1, const BRDF& aMaterial2);
	~Plane();
	bool Intersect(const Ray& aRay, aq_float* aT, Intersection* aIntersection);
private:
	vec3 mNormal;
	vec3 mOrigin;

	BRDF mSecondaryMaterial;
};

#endif