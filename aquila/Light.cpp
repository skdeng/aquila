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

DirectionalLight::DirectionalLight(const vec3& aColor, const vec3& aDirection, const float aIntensity)
{
	mColor = aColor;
	mDirection = aDirection;
	mIntensity = aIntensity;
}

void DirectionalLight::GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor)
{
	*aLightColor = mColor;
	aLightRay->Dir = -mDirection;
	aLightRay->Pos = aLocal.Pos;
}

PointLight::PointLight()
{

}

PointLight::PointLight(const vec3& aColor, const vec3& aPosition, const float aIntensity)
{
	mColor = aColor;
	mPosition = aPosition;
	mIntensity = aIntensity;

	//TODO
}

void PointLight::GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor)
{
	//TODO
}