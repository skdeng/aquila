#ifndef _AQ_PATHTRACER_H_
#define _AQ_PATHTRACER_H_

#include "Common.h"
#include "Types.h"
#include "Shape.h"
#include "Scene.h"

#include <random>

class Pathtracer
{
public:
	Pathtracer();
	~Pathtracer();

	Color Trace(const Ray& aRay, int aDepth = 0);
	void SetScene(Scene* aScene);

private:
	std::unique_ptr<Scene> mScene;
};

#endif