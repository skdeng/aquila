#include "Shape.h"

Primitive::Primitive()
{

}

Primitive::~Primitive()
{

}

Triangle::Triangle()
{
	
}

Triangle::Triangle(const vec3& aA, const vec3& aB, const vec3& aC, const Color& aColor)
{
	mA = aA;
	mB = aB;
	mC = aC;
	mColor = aColor;

	mAB = aB - aA;
	mAC = aC - aA;

	mNormal = cross(mAC, mAB);
	mNormal = normalize(mNormal);

	mMaterial.kd = mColor;
	mMaterial.ks = COLOR::WHITE;
	mMaterial.ka = mColor * 0.1f;
	mMaterial.kr = Color(0.2f, 0.2f, 0.2f);
}

Triangle::~Triangle()
{

}

bool Triangle::Intersect(const Ray& aRay, float* aT, Intersection* aIntersection)
{
	const vec3& RayOrigin = aRay.Pos;
	const vec3& RayDir = aRay.Dir;

	//check if ray is parallel to the plane
	//I consider tangent as non-intersecting
	float theta = dot(RayDir, mNormal);
	if (theta == 0)
		return false;

	//calculate intersection
	float tmpT = (dot(mA, mNormal) - dot(RayOrigin, mNormal)) / theta;

	//check boundaries
	if (tmpT < aRay.TMin || tmpT > aRay.TMax)
		return false;

	//Compute intersection point by explicitly computing it using the shape formula
	vec3 IntersectionPoint = RayOrigin + tmpT * RayDir;

	//check if the intersection point with the plane is inside the triangle
	if (!Inside(IntersectionPoint))
		return false;

	//Save value to given buffer
	if (aT != nullptr)
	{
		*aT = tmpT;
	}
	if (aIntersection != nullptr)
	{
		aIntersection->Local.Pos = IntersectionPoint;
		aIntersection->Local.Normal = mNormal;
		aIntersection->Material = mMaterial;
		aIntersection->Object = this;
	}

	return true;
}

void Triangle::GetBRDF(const LocalGeo& aLocal, BRDF* aBRDF)
{
	*aBRDF = mMaterial;
}

bool Triangle::Inside(const vec3& aPoint)
{
	vec3 BarycentricPoint;
	Barycentric(aPoint, &BarycentricPoint);
	DEBUG_LOG("Barycentric: (" + std::to_string(BarycentricPoint.x) + "," + std::to_string(BarycentricPoint.y) + "," + std::to_string(BarycentricPoint.z) + ")");
	if (BarycentricPoint.x < 0.0f || BarycentricPoint.x > 1.0f ||
		BarycentricPoint.y < 0.0f || BarycentricPoint.y > 1.0f ||
		BarycentricPoint.z < 0.0f || BarycentricPoint.z > 1.0f)
	{
		return false;
	}
	return true;
}

bool Triangle::Inside(const float afX, const float afY, const float afZ)
{
	return Inside(vec3(afX, afY, afZ));
}

Sphere::Sphere(const vec3& aCenter, const float aRadius, const BRDF& aMaterial)
{
	mCenter = aCenter;
	mRadius = aRadius;
	mMaterial = aMaterial;
}

Sphere::~Sphere()
{

}

bool Sphere::Intersect(const Ray& aRay, float* aT, Intersection* aIntersection)
{
	vec3 oc = aRay.Pos - mCenter;

	float det = std::pow(dot(aRay.Dir, oc), 2) - std::pow(length(oc), 2) + (mRadius * mRadius);

	//no intersection
	if (det < 0)
		return false;

	float tmpT = -dot(aRay.Dir, oc);

	//determinant larger than zero => 2 intersections
	if (det > 0)
	{
		float sqrtdet = std::sqrt(det);
		//find the closest intersection
		if (sqrtdet > tmpT)
			tmpT += sqrtdet;
		else
			tmpT -= sqrtdet;
	}
	
	if (aT)
	{
		*aT = tmpT;
	}
	if (aIntersection)
	{
		aIntersection->Object = this;
		aIntersection->Local.Pos = aRay.Pos + tmpT * aRay.Dir;
		aIntersection->Local.Normal = aIntersection->Local.Pos - mCenter;
		aIntersection->Local.Normal = normalize(aIntersection->Local.Normal);
		aIntersection->Material = mMaterial;
	}
	return true;
}

void Sphere::GetBRDF(const LocalGeo& aLocal, BRDF* aBRDF)
{
	aBRDF = &mMaterial;
}