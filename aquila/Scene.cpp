#include "Scene.h"
#include "rapidjson\document.h"

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
	mSceneObjects.push_back(new Plane(Transformation(MATRIX::I), MATERIAL::SILVER, MATERIAL::BLUE_MATT));
	mSceneObjects.push_back(new Sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, MATERIAL::BLUE_MATT));
	//mLights.push_back(new DirectionalLight(Color(1.0f, 1.0f, 0.8f), vec3(-1.0f, -1.0f, -1.0f), 1.0f));
	mLights.push_back(new PointLight(Color(1.0f, 1.0f, 1.0f), vec3(0.0f, 2.0f, 0.0f), 0.8f));
}

void Scene::InitScene(const char* aSceneFile)
{
	std::ifstream fin(aSceneFile);
	if (!fin.is_open())
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Failed to open scene file", ("Failed to open scene file: " + std::string(aSceneFile)).c_str(), NULL);
		return;
	}

	char FileBuf[1024];
	try
	{
		fin.get(FileBuf, 1024, '\0');
	}
	catch (std::ios::failure& e)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Failed to read scene file", ("Error occured reading scene file: " + std::string(e.what())).c_str(), NULL);
		return;
	}
	fin.close();

	rapidjson::Document Doc;
	Doc.Parse(FileBuf);

	mProperties.ImageWidth = Doc["image_width"].GetInt();
	mProperties.ImageHeight = Doc["image_height"].GetInt();
	mProperties.BackgroundColor = Color(Doc["background_color"].GetString());
	mProperties.PrimarySample = Doc["primary_sample"].GetInt();

	mProperties.CameraPos = vec3(Doc["cam"]["pos"].GetString());
	mProperties.CameraDir = vec3(Doc["cam"]["dir"].GetString());
	mProperties.CameraUp = vec3(Doc["cam"]["up"].GetString());

	//Parse scene lights
	for (auto itr = Doc["lights"].MemberBegin(); itr != Doc["lights"].MemberEnd(); itr++)
	{
		Light* NewLight;
		if (itr->value["type"].GetString() == "directional")
		{
			NewLight = new DirectionalLight(Color(itr->value["color"].GetString()), Color(itr->value["dir"].GetString()), itr->value["intensity"].GetDouble());
		}
		else if (itr->value["type"].GetString() == "point")
		{
			NewLight = new PointLight(Color(itr->value["color"].GetString()), Color(itr->value["pos"].GetString()), itr->value["intensity"].GetDouble());
		}
	}

	//Parse scene objects
	for (auto itr = Doc["objects"].MemberBegin(); itr != Doc["objects"].MemberEnd(); itr++)
	{
		Primitive* NewObj;
		if (itr->value["type"].GetString() == "sphere")
		{
			//TODO fix material
			NewObj = new Sphere(vec3(itr->value["center"].GetString()), itr->value["radius"].GetDouble(), BRDF());
		}
		else if (itr->value["type"].GetString() == "triangle")
		{
			//TODO add triangle
		}
	}
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