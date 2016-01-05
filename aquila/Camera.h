#ifndef _AQUILA_CAMERA_H_
#define _AQUILA_CAMERA_H_

#include "Common.h"

class Camera
{
public:
	Camera();
	Camera(const vec3& aPosition, const vec3& aDirection, const vec3& aUp, const aq_float aFOV, const int aScreenWidth, const int aScreenHeight);
	~Camera();

	void GetRay(const Sample& aSample, Ray* aRay, const aq_float offsetX, const aq_float offsetY);

	//! Set the position of the camera
	/*!
		\param aPosition New position of the camera in world space
	*/
	void SetPosition(const vec3& aPosition);

	//! Set the direction of the camera
	/*!
		\param aDirection New view vector of the camera in world space
		\param aUp New up vector of the camera in world space
	*/
	void SetDirection(const vec3& aDirection, const vec3& aUp);
	
	void SetVerticalFOV(const aq_float aFOV);

private:
	//! Position of the camera
	vec3 mPosition;
	//! Coordinate frame of the camera in world space
	vec3 mX_worldspace, mY_worldspace, mZ_worldspace;
	//! Coordinate frame to generate the ray
	vec3 mU, mV, mW;
	//! Field of view of the camera
	aq_float mFOV;
	//! Screen dimensions
	int mScreenWidth, mScreenHeight;
};

#endif