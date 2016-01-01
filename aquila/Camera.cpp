#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(const vec3& aPosition, const vec3& aDirection, const vec3& aUp, const float aFOV, const int aScreenWidth, const int aScreenHeight)
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

void Camera::GetRay(const Sample& aSample, Ray* aRay, double offsetX, double offsetY)
{
	double fovX = mFOV * mScreenWidth / mScreenHeight;
	
	double thetaX = std::tan(mFOV / 2.0);
	double thetaY = std::tan(mFOV / 2.0);
	double halfWidth = mScreenWidth / 2.0;
	double halfHeight = mScreenHeight / 2.0;
	double alpha = thetaX * ((aSample.x + offsetX) - halfWidth) / halfWidth;
	double beta = thetaY * (halfHeight - (aSample.y + offsetY)) / halfHeight;

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

void Camera::SetVerticalFOV(const float aFOV)
{
	mFOV = aFOV;
}