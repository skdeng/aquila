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
	*aLightColor = mColor * mIntensity;
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

	//TODO
}

PointLight::~PointLight()
{

}

void PointLight::GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor)
{
	aq_float LightDist = length(mPosition - aLocal.Pos);
	aq_float Attenuation = ConstantAttenuation + LightDist * LinearAttenuation + LightDist * LightDist * QuadraticAttenuation;
	*aLightColor = mColor * mIntensity;

	aLightRay->Dir = normalize(mPosition - aLocal.Pos);
	aLightRay->Pos = aLocal.Pos;
	aLightRay->TMax = ((mPosition - aLocal.Pos) / aLightRay->Dir).y;

	if (aLightRay->TMax < 1)
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "problem", std::string((mPosition - aLocal.Pos) / aLightRay->Dir).c_str(), 0);

	aLightRay->TMin = CONSTANT::RAY_MINIMUM;
}