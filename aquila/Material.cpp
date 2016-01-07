#include "Material.h"

Material::Material(BRDF * aBRDF)
{
	mBRDF = std::unique_ptr<BRDF>(aBRDF);
}

Color Material::ComputeBRDF(const Ray & aIncidentRay, const Ray & aReflectedRay, const LocalGeo & aLocal)
{
	return Color();
}

Lambertian::Lambertian(const Color& aColor)
{
	mColor = aColor;
}

Color Lambertian::Compute(const Ray& aIncidentRay, const Ray& aReflectedRay, const LocalGeo& aLocal)
{
	return mColor / M_PI;
}