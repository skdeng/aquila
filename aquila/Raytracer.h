#ifndef _AQUILA_RAYTRACER_H_
#define _AQUILA_RAYTRACER_H_

#include "Ray.h"
#include "Types.h"
#include "Shape.h"

#include <vector>

class Raytracer
{
public:
	Raytracer();
	~Raytracer();

	void Trace(const Ray& aRay, int aDepth, Color* aColor);

private:
	std::vector<Primitive> mScene;

	int mMaxDepth;
};

#endif