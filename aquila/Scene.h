#ifndef _AQUILA_SCENE_H_
#define _AQUILA_SCENE_H_

#include "Common.h"
#include "Light.h"
#include "Shape.h"

#include <vector>

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
	bool Intersect(const Ray& aRay, aq_float *aT, Intersection* aIntersection);
	//bool Intersect(const Ray& aRay);

	const std::vector<Light*>& GetLights()
	{
		return mLights;
	}

public:
	const Prop& Properties = mProperties;

private:
	std::vector<Primitive*> mSceneObjects;
	std::vector<Light*> mLights;
	std::vector<BRDF*> mMaterials;

	Prop mProperties;
};

#endif