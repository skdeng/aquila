#ifndef _AQUILA_UTILS_TYPE_H_
#define _AQUILA_UTILS_TYPE_H_

#include "glmath.h"


//! Precision of aq_floating number being used
typedef double aq_float;

typedef vec2 Sample;
typedef vec3 Color;

class Primitive;
struct Ray;

class Transformation
{
public:
	Transformation();
	Transformation(const mat4x4& aM);

	friend vec4 operator*(const Transformation& aM, const vec4& aV);
	friend vec3 operator*(const Transformation& aM, const vec3& aV);
	friend Ray operator*(const Transformation& aM, const Ray& aRay);

	mat4x4 mM, mMinv;
};

//! Local geometry at intersection point
struct LocalGeo
{
	vec3 Pos;
	vec3 Normal;
};

//! Bidirectional reflectance distribution function
struct BRDF
{
	//! Diffuse
	Color kd;
	//! Specular
	Color ks;
	//! Reflectance coefficient
	Color kr;
	
	//! Hardness for specular reflection
	aq_float Hardness;
	//! Transparency
	aq_float Transparency;
	aq_float RefractiveIndex;

	BRDF(){}
	BRDF(Color aKD, Color aKS, Color aKR, aq_float aHardness, aq_float aTransparency, aq_float aRefractiveIndex) :
		kd(aKD),
		ks(aKS),
		kr(aKR), 
		Hardness(aHardness),
		Transparency(aTransparency),
		RefractiveIndex(aRefractiveIndex)
	{}
};

//! Intersection point information in world-space
struct Intersection
{
	LocalGeo Local;
	BRDF Material;
	Primitive* Object = nullptr;
	int RecusiveDepth = 0;
};

#endif