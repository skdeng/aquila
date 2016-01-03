#include "Raytracer.h"

Raytracer::Raytracer()
{
}

Raytracer::~Raytracer()
{
	mScene.release();
}

void Raytracer::Trace(const Ray& aRay, Color* aColor)
{
	float T;
	Intersection RayIntersection;
	if (!mScene->Intersect(aRay, &T, &RayIntersection))
	{
		*aColor = mScene->Properties.BackgroundColor;
		return;
	}
	
	//*aColor = RayIntersection.Material.kd;
	*aColor = COLOR::BLACK;

	for (Light* light : mScene->GetLights())
	{
		*aColor += Shade(aRay, RayIntersection, *light);
	}

	*aColor = clamp(*aColor, 0.0f, 1.0f);

	//TODO handle reflection
}

void Raytracer::SetScene(Scene* aScene)
{
	mScene = std::unique_ptr<Scene>(aScene);
}

Color Raytracer::Shade(const Ray& aRay, const Intersection& aIntersection, Light& aLight)
{
	Ray ShadowRay;
	Color LightColor;
	aLight.GenerateLightRay(aIntersection.Local, &ShadowRay, &LightColor);
	if (mScene->Intersect(ShadowRay, nullptr, nullptr))
	{
		return Color(0.0f, 0.0f, 0.0f);
	}

	float LightRatio = 1.0;

	Color DiffuseColor, SpecularColor, AmbientColor;

	//Diffuse light
	float DiffuseIntensity = Utils::Clamp(dot(aIntersection.Local.Normal, ShadowRay.Dir), 0.0f, 1.0f);
	DiffuseColor = LightColor * DiffuseIntensity * aIntersection.Material.kd * LightRatio;

	//Ambient light
	AmbientColor = LightColor * aIntersection.Material.ka;

	//Specular light
	vec3 HalfVec = normalize(ShadowRay.Dir - aRay.Dir);
	double Alpha = Utils::Clamp(dot(HalfVec, aIntersection.Local.Normal), 0.0f, 1.0f);
	float SpecularIntensity = std::pow(Alpha, aIntersection.Material.hardness);
	SpecularColor = elemul(LightColor, aIntersection.Material.ks) * SpecularIntensity * LightRatio;

	return DiffuseColor + SpecularColor + AmbientColor;
}