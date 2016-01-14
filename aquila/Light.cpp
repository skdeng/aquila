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

DirectionalLight::DirectionalLight(const Color& aColor, const vec3& aDirection, const aq_float aIntensity)
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
	*aLightColor = mColor;
	aLightRay->Dir = -mDirection;
	aLightRay->Pos = aLocal.Pos;
	aLightRay->TMax = CONSTANT::RAY_MAXIMUM;
	aLightRay->TMin = CONSTANT::RAY_MINIMUM;
}

//============================================================================================================

const aq_float PointLight::ConstantAttenuation = 1.0;
const aq_float PointLight::LinearAttenuation = 0.007f;
const aq_float PointLight::QuadraticAttenuation = 0.0002f;

PointLight::PointLight()
{

}

PointLight::PointLight(const Color& aColor, const vec3& aPosition, const aq_float aIntensity)
{
	mColor = aColor;
	mPosition = aPosition;
	mIntensity = aIntensity;
}

PointLight::~PointLight()
{

}

void PointLight::GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor)
{
	aq_float LightDist = length(mPosition - aLocal.Pos);
	aq_float Attenuation = ConstantAttenuation + LightDist * LinearAttenuation + LightDist * LightDist * QuadraticAttenuation;
	*aLightColor = mColor * Attenuation;

	aLightRay->Dir = normalize(mPosition - aLocal.Pos);
	aLightRay->Pos = aLocal.Pos;
	aLightRay->TMax = ((mPosition - aLocal.Pos) / aLightRay->Dir).y;

	aLightRay->TMin = CONSTANT::RAY_MINIMUM;
}

//============================================================================================================

SphereLight::SphereLight(const Color & aColor, const vec3 & aPosition, const aq_float aRadius, const aq_float aIntensity)
{
	PointLight(aColor, aPosition, aIntensity);
	mRadius = aRadius;
}

void SphereLight::GenerateLightRay(const LocalGeo & aLocal, Ray * aLightRay, vec3 * aLightColor)
{
	vec3 RandomDirection = normalize(vec3(Utils::RandNormal(), Utils::RandNormal(), Utils::RandNormal()));
	vec3 LightSpherePoint = mPosition + mRadius * RandomDirection;

	aq_float LightDist = length(LightSpherePoint - aLocal.Pos);
	aq_float Attenuation = ConstantAttenuation + LightDist * LinearAttenuation + LightDist * LightDist * QuadraticAttenuation;
	*aLightColor = mColor;

	aLightRay->Dir = normalize(LightSpherePoint - aLocal.Pos);
	aLightRay->Pos = aLocal.Pos;
	aLightRay->TMax = ((LightSpherePoint - aLocal.Pos) / aLightRay->Dir).y;
	aLightRay->TMin = CONSTANT::RAY_MINIMUM;
}
