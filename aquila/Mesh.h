#ifndef _AQ_MESH_H_
#define _AQ_MESH_H_

#include "Shape.h"

class Mesh : public Primitive
{
public:
	Mesh();
	~Mesh();

	bool Load(const char* mFile);
	bool Intersect(const Ray& aRay, aq_float* aT, Intersection* aIntersection);
private:
	std::vector<Triangle*> mTriangles;
};

#endif