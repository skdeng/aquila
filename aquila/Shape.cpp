#include "Shape.h"

#include "Main.h"

Primitive::Primitive()
{

}

Primitive::~Primitive()
{

}

Primitive* Primitive::Transform(const Transformation& aM)
{
	mM = aM;
	return this;
}

//=================================================================================================

Triangle::Triangle(const vec3& aA, const vec3& aB, const vec3& aC, const BRDF& aMaterial)
{
	mA = aA;
	mB = aB;
	mC = aC;

	mAB = aB - aA;
	mAC = aC - aA;

	mNormal = cross(mAC, mAB);
	mNormal = normalize(mNormal);

	mMaterial = aMaterial;
}

Triangle::~Triangle()
{

}

bool Triangle::Intersect(const Ray& aRay, aq_float* aT, Intersection* aIntersection)
{
	const vec3& RayOrigin = aRay.Pos;
	const vec3& RayDir = aRay.Dir;

	//check if ray is parallel to the plane
	//I consider tangent as non-intersecting
	aq_float theta = dot(RayDir, mNormal);
	if (theta == 0)
		return false;

	//calculate intersection
	aq_float tmpT = (dot(mA, mNormal) - dot(RayOrigin, mNormal)) / theta;

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

bool Triangle::Inside(const vec3& aPoint)
{
	vec3 BarycentricPoint;
	Barycentric(aPoint, &BarycentricPoint);
	DEBUG_LOG("Barycentric: (" + std::to_string(BarycentricPoint.x) + "," + std::to_string(BarycentricPoint.y) + "," + std::to_string(BarycentricPoint.z) + ")");
	if (BarycentricPoint.x < 0.0 || BarycentricPoint.x > 1.0 ||
		BarycentricPoint.y < 0.0 || BarycentricPoint.y > 1.0 ||
		BarycentricPoint.z < 0.0 || BarycentricPoint.z > 1.0)
	{
		return false;
	}
	return true;
}

bool Triangle::Inside(const aq_float afX, const aq_float afY, const aq_float afZ)
{
	return Inside(vec3(afX, afY, afZ));
}

//=================================================================================================

Sphere::Sphere(const vec3& aCenter, const aq_float aRadius, const BRDF& aMaterial)
{
	mCenter = aCenter;
	mRadius = aRadius;
	mMaterial = aMaterial;
}

Sphere::~Sphere()
{

}

bool Sphere::Intersect(const Ray& aRay, aq_float* aT, Intersection* aIntersection)
{
	vec3 oc = aRay.Pos - mCenter;

	aq_float det = std::pow(dot(aRay.Dir, oc), 2) - std::pow(length(oc), 2) + (mRadius * mRadius);

	//no intersection
	if (det < 0)
		return false;

	aq_float tmpT = -dot(aRay.Dir, oc);

	//determinant larger than zero => 2 intersections
	if (det > 0)
	{
		aq_float sqrtdet = std::sqrt(det);
		//find the closest intersection
		if (sqrtdet > tmpT)
			tmpT += sqrtdet;
		else
			tmpT -= sqrtdet;
	}

	if (tmpT < aRay.TMin || tmpT > aRay.TMax)
		return false;

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

//=================================================================================================

Box::Box(const vec3& aMin, const vec3& aMax, const BRDF& aMaterial)
{
	mMin = aMin;
	mMax = aMax;
	mMaterial = aMaterial;
}

Box::~Box()
{

}

bool Box::Intersect(const Ray& aRay, aq_float* aT, Intersection* aIntersection)
{
	vec3 Diff = 1.0 / aRay.Dir;

	vec3 TMin = elemul(mMin - aRay.Pos, Diff);
	vec3 TMax = elemul(mMax - aRay.Pos, Diff);

	aq_float temp;
	if (Diff.x < 0)
	{
		temp = TMin.x;
		TMin.x = TMax.x;
		TMax.x = TMin.x;
	}
	if (Diff.y < 0)
	{
		temp = TMin.y;
		TMin.y = TMax.y;
		TMax.y = TMin.y;
	}
	if (Diff.z < 0)
	{
		temp = TMin.z;
		TMin.z = TMax.z;
		TMax.z = TMin.z;
	}

	aq_float MaxTMin = std::max({ TMin.x, TMin.y, TMin.z });
	aq_float MinTMax = std::min({ TMax.x, TMax.y, TMax.z });

	if (MaxTMin < 0 || MinTMax < 0 || MaxTMin > MinTMax)
	{
		//No intersection
		return false;
	}
	else
	{
		if (aT)
		{
			*aT = MaxTMin;
		}
		if (aIntersection)
		{
			aIntersection->Object = this;
			aIntersection->Material = mMaterial;
			aIntersection->Local.Pos = aRay + MaxTMin;
			//TODO finish local
		}
		return true;
	}
}

//=================================================================================================

Plane::Plane(const BRDF& aMaterial1, const BRDF& aMaterial2)
{
	mNormal = mM * vec3(0, 1, 0);
	mOrigin = mM * vec3(0, 0, 0);
	mMaterial = aMaterial1;
	mSecondaryMaterial = aMaterial2;
}

Plane::~Plane()
{

}

bool Plane::Intersect(const Ray& aRay, aq_float* aT, Intersection* aIntersection)
{
	Ray TRay = mM * aRay;
	aq_float Theta = dot(TRay.Dir, mNormal);

	if (Theta > -CONSTANT::PLANE_HORIZON && Theta < CONSTANT::PLANE_HORIZON)
	{
		return false;
	}
	else
	{
		aq_float k = dot(-TRay.Pos, mNormal);
		aq_float TmpT = dot(mOrigin - TRay.Pos, mNormal) / Theta;

		if (TmpT < aRay.TMin || TmpT > aRay.TMax)
			return false;

		if (aT)
		{
			*aT = TmpT;
		}
		if (aIntersection)
		{
			aIntersection->Object = this;
			aIntersection->Local.Normal = mNormal;
			aIntersection->Local.Pos = aRay + TmpT;

			if (int(std::floor(aIntersection->Local.Pos.x) + std::floor(aIntersection->Local.Pos.z)) % 2 == 0)
				aIntersection->Material = mMaterial;
			else
				aIntersection->Material = mSecondaryMaterial;
		}
		return true;
	}
}