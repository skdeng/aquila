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
	aq_float T;
	Intersection RayIntersection;
	if (!mScene->Intersect(aRay, &T, &RayIntersection))
	{
		*aColor = mScene->Properties.BackgroundColor;
		return;
	}
	
	*aColor = COLOR::BLACK;
	std::cout << mScene->GetLights().size() << std::endl;
	for (Light* light : mScene->GetLights())
	{
		*aColor += Shade(aRay, RayIntersection, *light);
	}

	*aColor = clamp(*aColor, 0.0, 1.0);

	//Reflection
	if (++RayIntersection.RecusiveDepth <= mScene->Properties.RecursiveDepth)
	{
		//Ray ReflectedRay(RayIntersection.Local.Pos, reflect(aRay.Dir, RayIntersection.Local.Normal));
		//Color ReflectedColor;
		//Trace(ReflectedRay, &ReflectedColor);
		//*aColor = mix(*aColor, ReflectedColor, RayIntersection.Material.kr);
		
		if (RayIntersection.Material.Transparency > 0)
		{
			Ray RefractedRay(RayIntersection.Local.Pos, refract(aRay.Dir, RayIntersection.Local.Normal, RayIntersection.Material.RefractiveIndex));
			Color RefractedColor;
			Trace(RefractedRay, &RefractedColor);
			*aColor = mix(*aColor, RefractedColor, RayIntersection.Material.Transparency);
		}
	}
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
		return Color(0.0, 0.0, 0.0);
	}

	aq_float LightRatio = 1.0;

	Color DiffuseColor, SpecularColor, AmbientColor;

	//Diffuse light
	aq_float DiffuseIntensity = Utils::Clamp(dot(aIntersection.Local.Normal, ShadowRay.Dir), 0.0, 1.0);
	DiffuseColor = LightColor * DiffuseIntensity * aIntersection.Material.kd * LightRatio;

	//Ambient light
	AmbientColor = 0.1 * aIntersection.Material.kd;

	//Specular light
	vec3 HalfVec = normalize(ShadowRay.Dir - aRay.Dir);
	double Alpha = Utils::Clamp(dot(HalfVec, aIntersection.Local.Normal), 0.0, 1.0);
	aq_float SpecularIntensity = std::pow(Alpha, aIntersection.Material.Hardness);
	SpecularColor = elemul(LightColor, aIntersection.Material.ks) * SpecularIntensity * LightRatio;
	
	return DiffuseColor + SpecularColor + AmbientColor;
}