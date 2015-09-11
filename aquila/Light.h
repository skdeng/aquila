#ifndef _AQUILA_LIGHT_H_
#define _AQUILA_LIGHT_H_

#include "Types.h"
#include "Ray.h"

class Light
{
public:
	Light();
	virtual ~Light();

	virtual void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor) = 0;
protected:
	vec3 mColor;
	float mIntensity;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(const vec3& aColor, const vec3& aDirection, const float aIntensity);
	~DirectionalLight();

	void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor);

private:
	vec3 mDirection;
};

class PointLight : public Light
{
public:
	PointLight();
	PointLight(const vec3& aColor, const vec3& aPosition, const float aIntensity);
	~PointLight();

	void GenerateLightRay(const LocalGeo& aLocal, Ray* aLightRay, vec3* aLightColor);

private:
	vec3 mPosition;
};

#endif