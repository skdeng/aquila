#ifndef _AQUILA_SAMPLER_H_
#define _AQUILA_SAMPLER_H_

#include "Common.h"

class Sampler
{
public:
	Sampler();
	Sampler(int aScreenWidth, int aScreenHeight);
	~Sampler();

	//! Get a sample at a specific pixel
	/*!
		\return true if pixel is within range of the screen, false otherwise
	*/
	bool GetSample(Sample* aSample, float aX, float aY);

	//! Get a sample at the next pixel
	/*!
		\return false if we reached beyong the last pixel, true otherwise
	*/
	bool GetSample(Sample* aSample);

private:
	int mScreenHeight, mScreenWidth;
	float mCurrentX, mCurrentY;
};

#endif