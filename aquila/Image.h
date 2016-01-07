#ifndef _AQUILA_IMAGE_H_
#define _AQUILA_IMAGE_H_

#include "Common.h"

#include <SDL.h>

class Image
{
public:
	Image(SDL_Renderer* aRenderer, const unsigned int aWidth, const unsigned int aHeight);
	~Image();

	void Commit(const Sample& aSample, const Color& aColor);
	void SetRenderer(SDL_Renderer* aRenderer);
	void Save(const char* aFile);

	void Bloom(double aThreshold);

private:
	inline uint32_t ColorToRGBA(const Color& aColor);

private:
	unsigned int mWidth;
	unsigned int mHeight;

	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
};

#endif