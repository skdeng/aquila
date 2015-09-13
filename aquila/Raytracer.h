#ifndef _AQUILA_RAYTRACER_H_
#define _AQUILA_RAYTRACER_H_

#include "Common.h"
#include "Light.h"
#include "Shape.h"
#include "Scene.h"

#include <vector>

class Raytracer
{
public:
	Raytracer();
	~Raytracer();

	void Trace(const Ray& aRay, int aDepth, Color* aColor);

private:
	Color Shade(const LocalGeo& aLocal, const BRDF& aBRDF, const Ray& aLightRay, const Color& aLightColor, const Light::LIGHT_TYPE aLightType);

private:
	Scene mScene;
};

#endif