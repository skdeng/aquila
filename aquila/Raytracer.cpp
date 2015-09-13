#include "Raytracer.h"

Raytracer::Raytracer()
{
	mScene.InitScene();
}

Raytracer::~Raytracer()
{
}

void Raytracer::Trace(const Ray& aRay, int aDepth, Color* aColor)
{
	PARANOID_PTR_CHECK(aColor, "RayTracer::Trace - aColor null pointer");

	//if depth exceed threshold
	if (aDepth > CONSTANT::SCENE_MAX_DEPTH)
	{
		*aColor = COLOR::BLACK;
		return;
	}

	float T;
	Intersection RayIntersection;
	if (!mScene.Intersect(aRay, &T, &RayIntersection))
	{
		*aColor = COLOR::BLACK;
		return;
	}

	BRDF IntersectionBRDF;
	RayIntersection.Object->GetBRDF(RayIntersection.Local, &IntersectionBRDF);

	for (Light* light : mScene.GetLights())
	{
		Ray LightRay;
		Color LightColor;
		light->GenerateLightRay(RayIntersection.Local, &LightRay, &LightColor);
		if (!mScene.Intersect(LightRay))
		{
			*aColor += Shade(RayIntersection.Local, IntersectionBRDF, LightRay, LightColor, light->GetType());
		}
	}

	//TODO handle reflection
}

Color Raytracer::Shade(const LocalGeo& aLocal, const BRDF& aBRDF, const Ray& aLightRay, const Color& aLightColor, const Light::LIGHT_TYPE aLightType)
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