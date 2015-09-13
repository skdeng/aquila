#ifndef _AQUILA_SCENE_H_
#define _AQUILA_SCENE_H_

#include "Common.h"
#include "Light.h"
#include "Shape.h"

#include <vector>

class Scene
{
public:
	Scene();
	~Scene();

	void InitScene();
	bool Intersect(const Ray& aRay, float *aT = nullptr, Intersection* aIntersection = nullptr);

	const std::vector<Light*>& GetLights()
	{
		return mLights;
	}
private:
	std::vector<Primitive*> mScene;
	std::vector<Light*> mLights;
};

#endif