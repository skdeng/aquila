#include "Pathtracer.h"

Pathtracer::Pathtracer()
{
	mScene = nullptr;
}

Pathtracer::~Pathtracer()
{
	
}

Color Pathtracer::Trace(const Ray & aRay, int aDepth)
{
	//TODO
	Color Flux;
	Intersection RayIntersection;
	aq_float T;

	//no intersection => background color
	if (!mScene->Intersect(aRay, &T, &RayIntersection))
		return mScene->Properties.BackgroundColor;

	//emissive color
	Flux += RayIntersection.Mat.ke;

	Color SurfaceColor = RayIntersection.Mat.kd;

	//Russian roulette for recursive termination
	aq_float MaxRefl = std::max(std::max(SurfaceColor.x, SurfaceColor.y), SurfaceColor.z);
	if (++aDepth > mScene->Properties.RecursiveDepth)
	{
		if (MaxRefl < Utils::RandFloatInterval(0.0, 1.2))
		{
			return RayIntersection.Mat.ke;
		}
		else
		{
			SurfaceColor /= MaxRefl;
		}
	}

	//Construct local reference frame
	vec3 W = -1 * RayIntersection.Local.Normal;
	vec3 U = normalize(cross(std::abs(W.x) > 0.1 ? vec3(0, 1, 0) : vec3(1, 0, 0), W));
	vec3 V = cross(W, U);
	
	aq_float R1 = 2 * M_PI * Utils::RandFloat();
	aq_float R2 = Utils::RandFloat();
	aq_float R2sqrt = std::sqrt(R2);
	vec3 D = normalize(U * cos(R1) * R2sqrt + V * sin(R1) * R2sqrt + W * std::sqrt(1 - R2));

	Ray ReflectedRay(RayIntersection.Local.Pos, D);
	Color ReflectedColor = elemul(SurfaceColor, Trace(ReflectedRay, aDepth));
	Flux += ReflectedColor;

	return Flux;
}

void Pathtracer::SetScene(Scene * aScene)
{
	mScene = std::unique_ptr<Scene>(aScene);
}
