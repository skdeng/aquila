#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{
	for (unsigned int i = 0; i < mScene.size(); i++)
	{
		if (mScene[i] != nullptr)
		{
			delete mScene[i];
			mScene[i] = nullptr;
		}
	}
	mScene.clear();

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
	mScene.push_back(new Triangle(vec3(1, 0, 0), vec3(0, 1, 0), vec3(-1, 0, 0), Color(0.5f, 0.1f, 0.8f)));

	mLights.push_back(new DirectionalLight(Color(1.0f, 1.0f, 0.8f), vec3(-1.0f, -1.0f, 1.0f), 0.2f));
}

bool Scene::Intersect(const Ray& aRay, float *aT, Intersection* aIntersection)
{
	//For now, check the whole scene
	//TODO use acceleration structure
	for (unsigned int i = 0; i < mScene.size(); i++)
	{
		if (mScene[i]->Intersect(aRay, aT, aIntersection))
		{
			return true;
		}
	}
	return false;
}