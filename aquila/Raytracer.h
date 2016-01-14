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

	void Trace(const Ray& aRay, Color* aColor, int aDepth = 0);
	void SetScene(Scene* aScene);

private:
	Color Shade(const Ray& aRay, const Intersection& aIntersection, Light& aLight);
	Color IndirectLighting(const Ray& aIncidentRay, const Intersection& aIntersection, int aDepth);

private:
	std::unique_ptr<Scene> mScene;
};

#endif