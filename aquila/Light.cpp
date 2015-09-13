#include "Light.h"

Light::Light()
{

}

Light::~Light()
{

}

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::DirectionalLight(const Color& aColor, const vec3& aDirection, const float aIntensity)
{
	mColor = aColor;
	mDirection = normalize(aDirection);
	mIntensity = aIntensity;
}

DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor)
{
	PARANOID_PTR_CHECK(aLightRay, "DirectionalLight::GenerateLightRay - aLightRay null pointer");
	PARANOID_PTR_CHECK(aLightColor, "DirectionalLight::GenerateLightRay - aLightColor null pointer");

	*aLightColor = mColor * mIntensity;
	aLightRay->Dir = -mDirection;
	aLightRay->Pos = aLocal.Pos;
	aLightRay->TMax = CONSTANT::RAY_MAXIMUM;
	aLightRay->TMin = CONSTANT::RAY_MINIMUM;
}

PointLight::PointLight()
{

}

PointLight::PointLight(const Color& aColor, const vec3& aPosition, const float aIntensity)
{
	mColor = aColor;
	mPosition = aPosition;
	mIntensity = aIntensity;

	//TODO
}

PointLight::~PointLight()
{

}

void PointLight::GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor)
{
	PARANOID_PTR_CHECK(aLightRay, "PointLight::GenerateLightRay - aLightRay null pointer");
	PARANOID_PTR_CHECK(aLightColor, "PointLight::GenerateLightRay - aLightColor null pointer");

	//TODO
}