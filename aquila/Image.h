#ifndef _AQUILA_IMAGE_H_
#define _AQUILA_IMAGE_H_

#include "Common.h"

#include <SDL.h>

class Image
{
public:
	Image(SDL_Renderer* aRenderer, const unsigned int aWidth, const unsigned int aHeight);
	~Image();

	void Commit(const Sample& aSample, Color aColor, aq_float aExposure = 1.0);
	void SetRenderer(SDL_Renderer* aRenderer);
	void Save(const char* aFile);

	void HDR(double aExposure);

	void Bloom(double aThreshold);

	void Render();

private:
	inline uint32_t ColorToRGBA(const Color& aColor);
	void BrightPassFilter(Color* aBrightColorBuffer, double aThreshold);

private:
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int mImageSize;

	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	Color* mHDRBuffer;
	aq_float* mLuminanceBuffer;

	const aq_float mMiddleGrey = 0.18;
};

#endif