#include "Raytracer.h"

Raytracer::Raytracer()
{
	mMaxDepth = 1000.0;
}

Raytracer::~Raytracer()
{

}

void Raytracer::Trace(const Ray& aRay, int aDepth, Color* aColor)
{
	if (aDepth > mMaxDepth)
	{
		*aColor = Color(0, 0, 0);
		return;
	}

	bool Intersect = false;
	float T;
	LocalGeo Geometry;
	for (int i = 0; i < mScene.size(); i++)
	{
		if (mScene[i].Intersect(aRay, &T, &Geometry))
		{
			Intersect = true;
			break;
		}
	}

	if (!Intersect)
	{
		*aColor = Color(0, 0, 0);
		return;
	}
}