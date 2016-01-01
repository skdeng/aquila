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
	//TODO
}