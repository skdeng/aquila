#ifndef _AQUILA_SCENE_H_
#define _AQUILA_SCENE_H_

#include "Common.h"
#include "Light.h"
#include "Shape.h"

#include <vector>
#include <unordered_map>

class Scene
{
public:
	static struct Prop
	{
		int ImageWidth = 800;
		int ImageHeight = 600;
		Color BackgroundColor = COLOR::BLACK;

		int PrimarySample = 4;

		vec3 CameraPos = vec3(1.0, 2.0, 10.0);
		vec3 CameraDir = vec3(0.0, -2.0, -10.0);
		vec3 CameraUp = vec3(0.0, 1.0, 0.0);

		int RecursiveDepth = 16;
	};

public:
	Scene();
	~Scene();

	void InitScene();
	void InitScene(const char* aSceneFile);
	bool Intersect(const Ray& aRay, aq_float *aT, Intersection* aIntersection)
	{
		bool intersect = false;

		if (aT) *aT = std::numeric_limits<aq_float>::infinity();

		//TODO use acceleration structure
		for (unsigned int i = 0; i < mSceneObjects.size(); i++)
		{
			aq_float tmpT;
			Intersection tmpIntersection;
			if (mSceneObjects[i]->Intersect(aRay, &tmpT, &tmpIntersection))
			{
				if (aT)
				{
					if (tmpT < *aT)
					{
						*aT = tmpT;
						if (aIntersection)
						{
							*aIntersection = tmpIntersection;
						}
					}
				}
				else
				{
					if (aIntersection)
					{
						*aIntersection = tmpIntersection;
					}
				}
				intersect = true;
			}
		}
		return intersect;
	}
	bool Intersect(const Ray& aRay);

	const std::vector<Light*>& GetLights()
	{
		return mLights;
	}

public:
	const Prop& Properties = mProperties;

private:
	std::vector<Primitive*> mSceneObjects;
	std::vector<Light*> mLights;
	std::unordered_map<std::string, BRDF*> mMaterial;

	Prop mProperties;
};

#endif