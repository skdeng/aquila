#include "Scene.h"
#include "rapidjson\document.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	for (auto itr = mMaterial.begin(); itr != mMaterial.end(); itr++)
	{
		if (itr->second != nullptr)
		{
			delete itr->second;
			itr->second = nullptr;
		}
	}
	mMaterial.clear();

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
	mSceneObjects.push_back(new Sphere(vec3(2, 0.5, 0.5), 0.5, MATERIAL::MIRROR));
	//mSceneObjects.push_back(new Triangle(vec3(0.0, 0.5, 3), vec3(-2, 0.5, 3), vec3(-1, 2, 3), MATERIAL::GLASS));
	//mLights.push_back(new DirectionalLight(Color(1.0, 1.0, 1.0), vec3(1, 1, -1), 1));
	mLights.push_back(new PointLight(Color(1.0, 1.0, 1.0), vec3(6.0, 2.0, 10.0), 0.8));
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

	char FileBuf[10240];
	try
	{
		fin.get(FileBuf, 10240, '\0');
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
	mProperties.ShadowRay = Doc["shadow_ray"].GetInt();
	mProperties.Exposure = Doc["exposure"].GetDouble();

	mProperties.CameraPos = vec3(Doc["cam"]["pos"].GetString());
	mProperties.CameraDir = vec3(Doc["cam"]["dir"].GetString());
	mProperties.CameraUp = vec3(Doc["cam"]["up"].GetString());

	//Parse materials
	for (rapidjson::SizeType i = 0; i < Doc["materials"].Size(); i++)
	{
		Material* Mat = new Material(
			Color(Doc["materials"][i]["emission"].GetString()),
			Color(Doc["materials"][i]["diffuse"].GetString()),
			Color(Doc["materials"][i]["specular"].GetString()),
			Color(Doc["materials"][i]["reflectance"].GetString()),
			Doc["materials"][i]["hardness"].GetDouble(),
			Doc["materials"][i]["transparency"].GetDouble(),
			Doc["materials"][i]["refractive_index"].GetDouble()
			);
		mMaterial.insert({ Doc["materials"][i]["name"].GetString(), Mat });
	}

	//Parse scene lights
	for (rapidjson::SizeType i = 0; i < Doc["lights"].Size(); i++)
	{
		Light* NewLight;
		std::string Type = Doc["lights"][i]["type"].GetString();
		if (Type == "directional")
		{
			NewLight = new DirectionalLight(Color(Doc["lights"][i]["color"].GetString()), Color(Doc["lights"][i]["dir"].GetString()), Doc["lights"][i]["intensity"].GetDouble());
		}
		else if (Type == "point")
		{
			NewLight = new PointLight(Color(Doc["lights"][i]["color"].GetString()), Color(Doc["lights"][i]["pos"].GetString()), Doc["lights"][i]["intensity"].GetDouble());
		}
		else if (Type == "sphere")
		{
			NewLight = new SphereLight(Color(Doc["lights"][i]["color"].GetString()), Color(Doc["lights"][i]["pos"].GetString()), Doc["lights"][i]["radius"].GetDouble(), Doc["lights"][i]["intensity"].GetDouble());
		}
		mLights.push_back(NewLight);
	}

	//Parse scene objects
	for (rapidjson::SizeType i = 0; i < Doc["objects"].Size(); i++)
	{
		Primitive* NewObj;
		std::string Type = Doc["objects"][i]["type"].GetString();
		if (Type == "sphere")
		{
			NewObj = new Sphere(
				vec3(Doc["objects"][i]["center"].GetString()),
				Doc["objects"][i]["radius"].GetDouble(),
				*mMaterial.at(Doc["objects"][i]["material"].GetString()));
		}
		else if (Type == "triangle")
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

bool Scene::Intersect(const Ray & aRay)
{
	for (unsigned int i = 0; i < mSceneObjects.size(); i++)
	{
		aq_float tmpT;
		Intersection tmpIntersection;
		if (mSceneObjects[i]->Intersect(aRay, &tmpT, &tmpIntersection))
		{
			return true;
		}
	}
	return false;
}
