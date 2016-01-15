#include "Pathtracer.h"

Pathtracer::Pathtracer()
{
	mScene = nullptr;
}

Pathtracer::~Pathtracer()
{
	
}

void Pathtracer::Trace(const Ray & aRay, Color * aColor)
{
	//TODO
	//rendering equation
}

void Pathtracer::SetScene(Scene * aScene)
{
	mScene = std::make_unique<Scene>(aScene);
}
