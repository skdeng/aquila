#include "Image.h"

Image::Image(SDL_Renderer* aRenderer, const unsigned int aWidth, const unsigned int aHeight)
{
	mWidth = aWidth;
	mHeight = aHeight;
	//mImageBuffer = new uint32_t[mWidth * mHeight];
	//memset(mImageBuffer, 0, mWidth * mHeight);
	mRenderer = aRenderer;
	mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);
}

Image::~Image()
{
	SDL_DestroyTexture(mTexture);
	//if (mImageBuffer != nullptr)
	//	delete[] mImageBuffer;
}

void Image::Commit(const Sample& aSample, const Color& aColor)
{
	SDL_Rect UpdateRect;
	UpdateRect.x = aSample.x;
	UpdateRect.y = aSample.y;
	UpdateRect.w = UpdateRect.h = 1;
	int pitch;

	void* TexturePixels;
	SDL_LockTexture(mTexture, &UpdateRect, &TexturePixels, &pitch);
	*((uint32_t*)TexturePixels) = ColorToRGBA(aColor);
	SDL_UnlockTexture(mTexture);
	SDL_RenderCopy(mRenderer, mTexture, &UpdateRect, &UpdateRect);
}

void Image::Update(const Sample& aSample)
{
	//SDL_DestroyTexture(mTexture);
	//SDL_Surface* TempSurface = SDL_CreateRGBSurfaceFrom(mImageBuffer, mWidth, mHeight, 32, 0, 0xFF000000, 0x00FF0000, 0x0000FF00, 0xFF);
	//mTexture = SDL_CreateTextureFromSurface(mRenderer, TempSurface);
	//SDL_FreeSurface(TempSurface);

	SDL_Rect UpdateRect;
	UpdateRect.x = aSample.x;
	UpdateRect.y = aSample.y;
	UpdateRect.w = UpdateRect.h = 1;

	SDL_UpdateTexture(mTexture, &UpdateRect, mImageBuffer + (int)aSample.y * mWidth + (int)aSample.x, 0);

	SDL_RenderCopy(mRenderer, mTexture, &UpdateRect, &UpdateRect);
}

void Image::SetRenderer(SDL_Renderer* aRenderer)
{
	mRenderer = aRenderer;
}

uint32_t Image::ColorToRGBA(const Color& aColor)
{
	uint32_t rgba = 0;
	rgba += ((unsigned int)(aColor.r * 0xFF)) << 24;
	rgba += ((unsigned int)(aColor.g * 0xFF)) << 16;
	rgba += ((unsigned int)(aColor.b * 0xFF)) << 8;
	rgba += 0xFF;
	return rgba;
}