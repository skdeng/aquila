#include "Raytracer.h"

bool refract(const vec3& i, const vec3& n, double ior_ratio, vec3& r) {
	auto cos_i = dot(-1 * i, n);
	auto cos_t2 = ((double)1) - ior_ratio * ior_ratio *  (((double)1) - cos_i * cos_i);
	if (cos_t2 <= 0)
		return false;
	r = ior_ratio * i + ((ior_ratio * cos_i - sqrt(abs(cos_t2))) * n);
	return true;
}

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

	for (Light* light : mScene->GetLights())
	{
		*aColor += Shade(aRay, RayIntersection, *light);
	}

	*aColor = clamp(*aColor, 0.0, 1.0);

	//Russian roulette for stopping recursive
	if (++RayIntersection.RecusiveDepth > mScene->Properties.RecursiveDepth)
	{
		aq_float AvgReflectance = sum(RayIntersection.Material.kr) / 3;
		if (AvgReflectance < Utils::RandFloatInterval(0.0, 1.2))
		{
			return;
		}
	}

	//Reflection
	if (sum(RayIntersection.Material.kr) > 0)
	{
		Ray ReflectedRay(RayIntersection.Local.Pos, reflect(aRay.Dir, RayIntersection.Local.Normal));
		Color ReflectedColor;
		Trace(ReflectedRay, &ReflectedColor);
		*aColor = mix(*aColor, ReflectedColor, RayIntersection.Material.kr);
	}

	////Refraction
	//if (RayIntersection.Material.Transparency > 0)
	//{
	//	Ray RefractedRay(RayIntersection.Local.Pos, refract(aRay.Dir, RayIntersection.Local.Normal, RayIntersection.Material.RefractiveIndex));
	//	Color RefractedColor;
	//	Trace(RefractedRay, &RefractedColor);
	//	*aColor = mix(*aColor, RefractedColor, RayIntersection.Material.Transparency);
	//}
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
	if (mScene->Intersect(ShadowRay))
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