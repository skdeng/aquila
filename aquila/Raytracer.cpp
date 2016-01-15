#include "Raytracer.h"

Raytracer::Raytracer()
{
}

Raytracer::~Raytracer()
{
	mScene.release();
}

void Raytracer::Trace(const Ray& aRay, Color* aColor, int aDepth)
{
	aq_float T;
	
	Intersection RayIntersection;

	if (!mScene->Intersect(aRay, &T, &RayIntersection))
	{
		*aColor = mScene->Properties.BackgroundColor;
		return;
	}
	
	*aColor = COLOR::BLACK;

	for (Light* light : mScene->GetLights())
	{
		*aColor += Shade(aRay, RayIntersection, *light);
	}

	*aColor = clamp(*aColor, 0.0, 100.0);

	//Russian roulette for stopping recursive
	if (aDepth > mScene->Properties.RecursiveDepth)
	{
		aq_float AvgReflectance = sum(RayIntersection.Mat.kr) / 3;
		if (AvgReflectance < Utils::RandFloatInterval(0.0, 1.2))
		{
			return;
		}
	}

	//Ambient occlusion
	//*aColor += 0.2 * IndirectLighting(aRay, RayIntersection, aDepth);

	//Reflection
	if (sum(RayIntersection.Mat.kr) > 0)
	{
		Ray ReflectedRay(RayIntersection.Local.Pos, reflect(aRay.Dir, RayIntersection.Local.Normal));
		Color ReflectedColor;
		Trace(ReflectedRay, &ReflectedColor, aDepth + 1);
		*aColor = mix(*aColor, ReflectedColor, RayIntersection.Mat.kr);
	}

	////Refraction
	if (RayIntersection.Mat.Transparency > 0)
	{
		Ray RefractedRay(RayIntersection.Local.Pos, refract(aRay.Dir, RayIntersection.Local.Normal, RayIntersection.Mat.RefractiveIndex));
		Color RefractedColor;
		Trace(RefractedRay, &RefractedColor, aDepth + 1);
		*aColor = mix(*aColor, RefractedColor, RayIntersection.Mat.Transparency);
	}
}

void Raytracer::SetScene(Scene* aScene)
{
	mScene = std::unique_ptr<Scene>(aScene);
}

Color Raytracer::Shade(const Ray& aRay, const Intersection& aIntersection, Light& aLight)
{
	aq_float LightRatio = 1.0;
	//Create 2 vectors orthonormal to the intersection normal and to each other
	vec3 rand = vec3(Utils::RandNormal(), Utils::RandNormal(), Utils::RandNormal());
	vec3 U = normalize(cross(aIntersection.Local.Normal, rand));
	vec3 V = normalize(cross(U, aIntersection.Local.Normal));
	for (int i = 0; i < mScene->Properties.ShadowRay; i++)
	{
		vec3 Alpha = Utils::RandNormal() * U * 0.2;
		vec3 Beta = Utils::RandNormal() * V * 0.2;
		Ray TempShadowRay;
		Color TempLightColor;
		aLight.GenerateLightRay(aIntersection.Local, &TempShadowRay, &TempLightColor);
		TempShadowRay.Dir += Alpha + Beta;
		if (mScene->Intersect(TempShadowRay))
			LightRatio -= 1.0 / mScene->Properties.ShadowRay;
	}

	Ray ShadowRay;
	Color LightColor;
	aLight.GenerateLightRay(aIntersection.Local, &ShadowRay, &LightColor);

	//Emissive light
	Color EmissiveColor = aIntersection.Mat.ke;

	//Diffuse light
	aq_float DiffuseIntensity = std::max(dot(aIntersection.Local.Normal, ShadowRay.Dir), 0.0);
	Color DiffuseColor = LightColor * DiffuseIntensity * aIntersection.Mat.kd * LightRatio;

	//Specular light
	vec3 HalfVec = normalize(ShadowRay.Dir - aRay.Dir);
	double Alpha = std::max(dot(HalfVec, aIntersection.Local.Normal), 0.0);
	aq_float SpecularIntensity = std::pow(Alpha, aIntersection.Mat.Hardness);
	Color SpecularColor = elemul(LightColor, aIntersection.Mat.ks) * SpecularIntensity * LightRatio;

	return EmissiveColor + DiffuseColor + SpecularColor;
}

Color Raytracer::IndirectLighting(const Ray & aIncidentRay, const Intersection& aIntersection, int aDepth)
{
	int SecondaryRays = 1;

	Color AccumulatedColor;
	
	//Create 2 vectors orthonormal to the intersection normal and to each other
	vec3 rand = vec3(Utils::RandNormal(), Utils::RandNormal(), Utils::RandNormal());
	vec3 U = normalize(cross(aIntersection.Local.Normal, rand));
	vec3 V = normalize(cross(U, aIntersection.Local.Normal));

	for (int i = 0; i < SecondaryRays; i++)
	{
		vec3 Alpha = Utils::RandNormal() * U;
		vec3 Beta = Utils::RandNormal() * V;

		Ray ReflectedRay(aIntersection.Local.Pos, normalize(aIntersection.Local.Normal + Alpha + Beta));

		Color TempColor;

		Trace(ReflectedRay, &TempColor, aDepth + 1);

		AccumulatedColor += TempColor;
	}
	return AccumulatedColor / SecondaryRays;
}
