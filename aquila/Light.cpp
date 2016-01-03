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

//============================================================================================================

const float PointLight::ConstantAttenuation = 1.0f;
const float PointLight::LinearAttenuation = 0.007f;
const float PointLight::QuadraticAttenuation = 0.0002f;

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
	float LightDist = length(mPosition - aLocal.Pos);
	float Attenuation = ConstantAttenuation + LightDist * LinearAttenuation + LightDist * LightDist * QuadraticAttenuation;
	*aLightColor = mColor * mIntensity;

	aLightRay->Dir = normalize(mPosition - aLocal.Pos);
	aLightRay->Pos = aLocal.Pos;
	aLightRay->TMax = CONSTANT::RAY_MAXIMUM;
	aLightRay->TMin = CONSTANT::RAY_MINIMUM;
}