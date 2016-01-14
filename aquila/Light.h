#ifndef _AQUILA_LIGHT_H_
#define _AQUILA_LIGHT_H_

#include "Common.h"
#include "Shape.h"

class Light
{
public:
	static enum LightType
	{
		DIRECTIONAL,
		POINT,
		SPHERE
	};

	Light();
	virtual ~Light();

	virtual void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor) = 0;
	virtual LightType GetType() = 0;

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
	LightType GetType()
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

	virtual void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor);
	LightType GetType()
	{
		return POINT;
	}
protected:
	static const aq_float ConstantAttenuation;
	static const aq_float LinearAttenuation;
	static const aq_float QuadraticAttenuation;

	vec3 mPosition;
};

class SphereLight : public PointLight
{
public:
	SphereLight(const Color& aColor, const vec3& aPosition, const aq_float aRadius, const aq_float aIntensity);
	void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor);

	LightType GetType()
	{
		return SPHERE;
	}
private:
	aq_float mRadius;
};

#endif