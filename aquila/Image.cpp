#include "Image.h"

Image::Image(SDL_Renderer* aRenderer, const unsigned int aWidth, const unsigned int aHeight)
{
	mWidth = aWidth;
	mHeight = aHeight;
	mColorBuffer = new uint32_t*[mHeight];
	for (unsigned int i = 0; i < mHeight; i++)
	{
		mColorBuffer[i] = new uint32_t[mWidth];
	}

	mRenderer = aRenderer;
	mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_RGBA4444, SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);
}

Image::~Image()
{
	SDL_DestroyTexture(mTexture);

	if (mColorBuffer != nullptr)
	{
		for (unsigned int i = 0; i < mHeight; i++)
		{
			if (mColorBuffer[i] != nullptr)
			{
				delete[] mColorBuffer[i];
				mColorBuffer[i] = nullptr;
			}
		}
		delete[] mColorBuffer;
		mColorBuffer = nullptr;
	}
}

void Image::Commit(const Sample& aSample, const Color& aColor)
{
	mColorBuffer[(unsigned int)aSample.y][(unsigned int)aSample.x] = ColorToRGBA(aColor);
}

void Image::Update(const Sample& aSample)
{
	SDL_Rect updateRect;
	updateRect.x = aSample.x;
	updateRect.y = aSample.y;
	updateRect.w = updateRect.h = 1;
	SDL_LockTexture(mTexture, &updateRect, (void**)(mColorBuffer + updateRect.y * mWidth + updateRect.x), 0);
	SDL_UnlockTexture(mTexture);

	SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);

	for (unsigned int i = 0; i < mHeight; i++)
	{
		for (unsigned int j = 0; j < mWidth; j++)
		{
			if (mColorBuffer[i][j] > 0xFF)
			{
				std::cout << mColorBuffer[i][j] << std::endl;
			}
		}
	}
}

void Image::SetRenderer(SDL_Renderer* aRenderer)
{
	mRenderer = aRenderer;
}

uint32_t Image::ColorToRGBA(const Color& aColor)
{
	uint32_t rgba = 0;
	rgba += ((unsigned int)(aColor.r * 0xFF)) << 24;
	rgba += ((unsigned int)(aColor.b * 0xFF)) << 16;
	rgba += ((unsigned int)(aColor.g * 0xFF)) << 8;
	rgba += 0xFF;

	return rgba;
}