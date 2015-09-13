#ifndef _AQUILA_LIGHT_H_
#define _AQUILA_LIGHT_H_

#include "Common.h"

class Light
{
public:
	static enum LIGHT_TYPE
	{
		DIRECTIONAL,
		POINT,
		GENERIC_LIGHT
	};

	Light();
	virtual ~Light();

	virtual void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor) = 0;
	virtual const LIGHT_TYPE GetType() = 0;
protected:
	vec3 mColor;
	float mIntensity;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(const Color& aColor, const vec3& aDirection, const float aIntensity);
	~DirectionalLight();

	void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor);
	const LIGHT_TYPE GetType()
	{
		return mType;
	}
private:
	vec3 mDirection;
	const LIGHT_TYPE mType = DIRECTIONAL;
};

class PointLight : public Light
{
public:
	PointLight();
	PointLight(const Color& aColor, const vec3& aPosition, const float aIntensity);
	~PointLight();

	void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor);
	const LIGHT_TYPE GetType()
	{
		return mType;
	}
private:
	vec3 mPosition;
	const LIGHT_TYPE mType = POINT;
};

#endif