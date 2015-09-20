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

	void Barycentric(const vec3 &p, const vec3 &a, const vec3 &b, const vec3 &c, float *u, float *v, float *w)
	{
		vec3 v0 = b - a, v1 = c - a, v2 = p - a;
		float d00 = dot(v0, v0);
		float d01 = dot(v0, v1);
		float d11 = dot(v1, v1);
		float d20 = dot(v2, v0);
		float d21 = dot(v2, v1);
		float denom = d00 * d11 - d01 * d01;
		*v = (d11 * d20 - d01 * d21) / denom;
		*w = (d00 * d21 - d01 * d20) / denom;
		*u = 1.0f - *v - *w;
	}

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