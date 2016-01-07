#ifndef _AQUILA_MATERIAL_H_
#define _AQUILA_MATERIAL_H_

#include "Common.h"
#include <memory>

//! Bidirectional reflectance distribution function
class BRDF
{
public:
	virtual Color Compute(const Ray& aIncidentRay, const Ray& aReflectedRay, const LocalGeo& aLocal) = 0;
};

class Material
{
public:
	Material() {}
	Material(BRDF* aBRDF);
	Color ComputeBRDF(const Ray& aIncidentRay, const Ray& aReflectedRay, const LocalGeo& aLocal);
private:
	std::unique_ptr<BRDF> mBRDF;

	//! Emission
	Color mEmissiveColor;
};

class Lambertian : public BRDF
{
public:
	Lambertian(const Color& aColor);
	Color Compute(const Ray& aIncidentRay, const Ray& aReflectedRay, const LocalGeo& aLocal);

private:
	Color mColor;
};

#endif