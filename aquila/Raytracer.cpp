#include "Raytracer.h"

Raytracer::Raytracer()
{
}

Raytracer::~Raytracer()
{
}

void Raytracer::Trace(const Ray& aRay, Color* aColor)
{
	float T;
	Intersection RayIntersection;
	if (!mScene->Intersect(aRay, &T, &RayIntersection))
	{
		*aColor = COLOR::BLACK;
		return;
	}
	
	*aColor = RayIntersection.Material.kd;

	//std::cout << std::string(RayIntersection.Material.kd) << std::endl;
	//for (Light* light : mScene.GetLights())
	//{
	//	Ray LightRay;
	//	Color LightColor;
	//	light->GenerateLightRay(RayIntersection.Local, &LightRay, &LightColor);
	//	if (!mScene.Intersect(LightRay, nullptr, nullptr))
	//	{
	//		*aColor += Shade(RayIntersection.Local, IntersectionBRDF, LightRay, LightColor, light->GetType());
	//	}
	//}

	//TODO handle reflection
}

void Raytracer::SetScene(Scene* aScene)
{
	mScene = std::unique_ptr<Scene>(aScene);
}

Color Raytracer::Shade(const LocalGeo& aLocal, const BRDF& aBRDF, const Ray& aLightRay, const Color& aLightColor, const Light::LightType aLightType)
{
	Color DiffuseColor, SpecularColor, AmbientColor;

	switch (aLightType)
	{
		case Light::DIRECTIONAL:
		{
			//Directional light
			float DiffuseIntensity = Utils::Clamp(dot(aLocal.Normal, aLightRay.Dir), 0.0f, 1.0f);
			DiffuseColor = aLightColor * DiffuseIntensity * aBRDF.kd;

			//Ambient light
			AmbientColor = aLightColor * aBRDF.ka;

			//Specular light
			break;
		}
	}

	return DiffuseColor + SpecularColor + AmbientColor;
}