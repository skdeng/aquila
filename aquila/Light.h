#ifndef _AQUILA_LIGHT_H_
#define _AQUILA_LIGHT_H_

#include "Common.h"

class Light
{
public:
	static enum LightType
	{
		DIRECTIONAL,
		POINT,
		GENERIC_LIGHT
	};

	Light();
	virtual ~Light();

	virtual void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor) = 0;
	virtual const LightType GetType() = 0;

protected:
	vec3 mColor;
	aq_float mIntensity;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(const Color& aColor, const vec3& aDirection, const aq_float aIntensity);
	~DirectionalLight();

	void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor);
	const LightType GetType()
	{
		return DIRECTIONAL;
	}
private:
	vec3 mDirection;
};

class PointLight : public Light
{
public:
	PointLight();
	PointLight(const Color& aColor, const vec3& aPosition, const aq_float aIntensity);
	~PointLight();

	void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor);
	const LightType GetType()
	{
		return POINT;
	}
private:
	static const aq_float ConstantAttenuation;
	static const aq_float LinearAttenuation;
	static const aq_float QuadraticAttenuation;

	vec3 mPosition;

};

#endif