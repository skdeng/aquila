#include "Scene.h"
#include "rapidjson\document.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (unsigned int i = 0; i < mMaterials.size(); i++)
	{
		if (mMaterials[i] != nullptr)
		{
			delete mMaterials[i];
			mMaterials[i] = nullptr;
		}
	}
	mMaterials.clear();

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
	mSceneObjects.push_back(new Plane(MATERIAL::SILVER, MATERIAL::BLUE_MATT));
	mSceneObjects.push_back(new Sphere(vec3(0, 1, 0), 1.0, MATERIAL::GOLD));
	mSceneObjects.push_back(new Sphere(vec3(2, 0.7, 0), 0.5, MATERIAL::BLUE_MATT));
	mSceneObjects.push_back(new Triangle(vec3(0.0, 0.5, 3), vec3(-2, 0.5, 3), vec3(-1, 2, 3), MATERIAL::GLASS));
	//mLights.push_back(new DirectionalLight(Color(1.0, 1.0, 1.0), vec3(1, 1, -1), 1));
	mLights.push_back(new PointLight(Color(1.0, 1.0, 1.0), vec3(6.0, 4.0, 10.0), 0.8));
	mLights.push_back(new PointLight(Color(1.0, 1.0, 1.0), vec3(-2.0, 1.0, 4.0), 0.8));
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
	mLights.reserve(Doc["lights"]["count"].GetInt());
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
		mLights.push_back(NewLight);
	}

	//Parse scene objects
	mSceneObjects.reserve(Doc["object"]["count"].GetInt());
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
		mSceneObjects.push_back(NewObj);
	}
}

bool Scene::Intersect(const Ray& aRay, aq_float *aT, Intersection* aIntersection)
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