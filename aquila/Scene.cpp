#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (unsigned int i = 0; i < mSceneObjects.size(); i++)
	{
		if (mSceneObjects[i] != nullptr)
		{
			delete mSceneObjects[i];
			mSceneObjects[i] = nullptr;
		}
	}
	mSceneObjects.clear();

	for (unsigned int i = 0; i < mLights.size(); i++)
	{
		if (mLights[i] != nullptr)
		{
			delete mLights[i];
			mLights[i] = nullptr;
		}
	}
	mLights.clear();
}

void Scene::InitScene()
{
	mSceneObjects.push_back(new Sphere(vec3(0, 0, 0), 2.0, BRDF(COLOR::RED, COLOR::GREEN, COLOR::BLUE, Color(1, 0, 0))));

	mLights.push_back(new DirectionalLight(Color(1.0f, 1.0f, 0.8f), vec3(-1.0f, -1.0f, 1.0f), 0.2f));
}

bool Scene::Intersect(const Ray& aRay, float *aT, Intersection* aIntersection)
{
	bool intersect = false;

	if (aT) *aT = std::numeric_limits<float>::infinity();

	//TODO use acceleration structure
	for (unsigned int i = 0; i < mSceneObjects.size(); i++)
	{
		float tmpT;
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