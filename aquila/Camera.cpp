#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(const vec3& aPosition, const vec3& aDirection, const vec3& aUp, const aq_float aFOV, const int aScreenWidth, const int aScreenHeight)
{
	SetPosition(aPosition);
	SetDirection(aDirection, aUp);
	SetVerticalFOV(aFOV);
	mScreenWidth = aScreenWidth;
	mScreenHeight = aScreenHeight;
}

Camera::~Camera()
{

}

void Camera::GetRay(const Sample& aSample, Ray* aRay, const aq_float offsetX, const aq_float offsetY)
{
	aq_float FOVX = mFOV * mScreenWidth / mScreenHeight;
	
	aq_float thetaX = (aq_float)std::tan(Utils::DegToRad(FOVX) / 2.0);
	aq_float thetaY = (aq_float)std::tan(Utils::DegToRad(mFOV) / 2.0);
	aq_float halfWidth = mScreenWidth / 2.0;
	aq_float halfHeight = mScreenHeight / 2.0;
	aq_float alpha = thetaX * ((aSample.x + offsetX) - halfWidth) / halfWidth;
	aq_float beta = thetaY * (halfHeight - (aSample.y + offsetY)) / halfHeight;

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
	mW = -1 * aDirection;	mW = normalize(mW);
	mU = cross(aUp, mW);	mU = normalize(mU);
	mV = cross(mW, mU);		mV = normalize(mV);
}

void Camera::SetVerticalFOV(const aq_float aFOV)
{
	mFOV = aFOV;
}