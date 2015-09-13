#include "Camera.h"

Camera::Camera(const vec3& aPosition, const vec3& aDirection, const vec3& aUp, const float aFOV, const int aScreenWidth, const int aScreenHeight)
{
	SetPosition(aPosition);
	SetDirection(aDirection, aUp);
	SetFOV(aFOV);
	mScreenWidth = aScreenWidth;
	mScreenHeight = aScreenHeight;
}

Camera::~Camera()
{

}

void Camera::GetRay(const Sample& aSample, Ray* aRay)
{
	PARANOID_PTR_CHECK(aRay, "Camera::GetRay - aRay null pointer");

	float alpha = std::tan(mFOV / 2.0f) * (aSample.x - (mScreenWidth / 2.0f)) / (mScreenWidth / 2.0f);
	//we have invert along Y-axis before the value of the coordinate increases from top to bottom
	float beta = std::tan(mFOV / 2.0f) * ((mScreenWidth / 2.0f) - aSample.y) / (mScreenWidth / 2.0f);

	aRay->Pos = mPosition;
	aRay->Dir = normalize(alpha * mU + beta * mV - mW);
	aRay->TMax = CONSTANT::RAY_MAXIMUM;
	aRay->TMin = CONSTANT::RAY_MINIMUM;
}

void Camera::SetPosition(const vec3& aPosition)
{
	mPosition = aPosition;
}

void Camera::SetDirection(const vec3& aDirection, const vec3& aUp)
{
	//Camera look down the minus Z-axis
	mZ_worldspace = -1 * aDirection;
	mY_worldspace = aUp;
	mX_worldspace = cross(mY_worldspace, mZ_worldspace);

	mW = -1 * aDirection;	mW = normalize(mW);
	mU = cross(aUp, mW);	mU = normalize(mU);
	mV = cross(mW, mU);		mV = normalize(mV);
}

void Camera::SetDirection(const float aHorizontalAngle, const float aVerticalAngle, const float aSpinAngle)
{
	//TODO
	//vec3 HorizontalVector = vec3(0,0,-1)
}

void Camera::SetFOV(const float aFOV)
{
	mFOV = aFOV;
}