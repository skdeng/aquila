#ifndef _AQ_PATHTRACER_H_
#define _AQ_PATHTRACER_H_

#include "Common.h"
#include "Shape.h"
#include "Scene.h"

class Pathtracer
{
public:
	Pathtracer();
	~Pathtracer();

	void Trace(const Ray& aRay, Color* aColor);
	void SetScene(Scene* aScene);
private:
	std::unique_ptr<Scene> mScene;
};

#endif