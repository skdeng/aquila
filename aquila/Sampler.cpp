#include "Sampler.h"

Sampler::Sampler(int aScreenWidth, int aScreenHeight)
{
	mScreenWidth = aScreenWidth;
	mScreenHeight = aScreenHeight;

	mCurrentX = 0;
	mCurrentY = 0;
}

Sampler::~Sampler()
{

}

bool Sampler::GetSample(Sample* aSampler, aq_float aX, aq_float aY)
{
	if (aX >= mScreenWidth || aY >= mScreenHeight)
		return false;

	if (aSampler == nullptr)
		aSampler = new Sample();

	aSampler->x = aX;
	aSampler->y = aY;

	return true;
}

bool Sampler::GetSample(Sample* aSampler)
{
	if (mCurrentX >= mScreenWidth || mCurrentY >= mScreenHeight)
		return false;

	if (aSampler == nullptr)
		aSampler = new Sample();

	aSampler->x = mCurrentX;
	aSampler->y = mCurrentY;

	if (++mCurrentX >= mScreenWidth)
	{
		mCurrentX = 0;
		mCurrentY++;
	}	

	return true;
}