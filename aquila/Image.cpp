#include "Image.h"

Image::Image(SDL_Renderer* aRenderer, const unsigned int aWidth, const unsigned int aHeight)
{
	mWidth = aWidth;
	mHeight = aHeight;
	mImageSize = mWidth * mHeight;
	mRenderer = aRenderer;
	mTexture = SDL_CreateTexture(aRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);
	mHDRBuffer = new Color[mWidth * mHeight];

	mLuminanceBuffer = nullptr;
}

Image::~Image()
{
	SDL_DestroyTexture(mTexture);
	delete[] mHDRBuffer;
	if (mLuminanceBuffer != nullptr)
		delete[] mLuminanceBuffer;
}

void Image::Commit(const Sample& aSample, Color aColor, aq_float aExposure)
{
	mHDRBuffer[(int)aSample.y * mWidth + (int)aSample.x] = aColor;

	aColor = Color(1.0) - exp(-aColor * aExposure);

	SDL_Rect UpdateRect;
	UpdateRect.x = (int)aSample.x;
	UpdateRect.y = (int)aSample.y;
	UpdateRect.w = UpdateRect.h = 1;
	int pitch;

	void* TexturePixels;
	SDL_LockTexture(mTexture, &UpdateRect, &TexturePixels, &pitch);
	*((uint32_t*)TexturePixels) = ColorToRGBA(clamp(pow(aColor, 1.0/2.2), 0, 1));
	SDL_UnlockTexture(mTexture);
	SDL_RenderCopy(mRenderer, mTexture, &UpdateRect, &UpdateRect);
}

void Image::SetRenderer(SDL_Renderer* aRenderer)
{
	mRenderer = aRenderer;
}

void Image::Save(const char* aFile)
{
	SDL_Surface* SaveSurface = SDL_CreateRGBSurface(0, mWidth, mHeight, 32, 0xFF000000, 0xFF0000, 0xFF00, 0xFF);
	if (!SaveSurface)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Failed to save image", SDL_GetError(), NULL);
		return;
	}
	if (SDL_RenderReadPixels(mRenderer, NULL, SaveSurface->format->format, SaveSurface->pixels, SaveSurface->pitch) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Failed to save image", SDL_GetError(), NULL);
		return;
	}
	if (SDL_SaveBMP(SaveSurface, aFile) < 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Failed to save image", SDL_GetError(), NULL);
		return;
	}
	SDL_FreeSurface(SaveSurface);
}

void Image::HDR(double aExposure)
{
	const aq_float Gamma = 2.2;
	
	for (int i = 0; i < mImageSize; i++)
	{
		//exposure tone mapping
		mHDRBuffer[i] = Color(1.0) - exp(-mHDRBuffer[i] * aExposure);
	}
}

void Image::Bloom(double aThreshold)
{
	Color* BrightBuffer = new Color[mImageSize];
	BrightPassFilter(BrightBuffer, aThreshold);

	aq_float Weight[5] = { 0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216 };

	//horizontal blur
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			int p = y * mWidth + x;
			for (int i = 0; i < 5; i++)
			{
				if (p + i < mImageSize)
					mHDRBuffer[p] += Weight[i] * mHDRBuffer[p + i];
				if (p - i > 0)
					mHDRBuffer[p] += Weight[i] * mHDRBuffer[p - i];
			}
		}
	}

	//vertical blur
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			int p = y * mWidth + x;
			for (int i = 0; i < 5; i++)
			{
				if ((p + mWidth * i) < mImageSize)
					mHDRBuffer[p] += Weight[i] * mHDRBuffer[p + mWidth * i];
				std::cout << p - mWidth * i << std::endl;
				if ((p - mWidth * i) > 0)
					mHDRBuffer[p] += Weight[i] * mHDRBuffer[p - mWidth * i];
			}
		}
	}
}

void Image::Render()
{
	SDL_Rect UpdateRect;
	UpdateRect.x = 0;
	UpdateRect.y = 0;
	UpdateRect.w = mWidth;
	UpdateRect.h = mHeight;
	int pitch;

	void* TexturePixels;
	SDL_LockTexture(mTexture, &UpdateRect, &TexturePixels, &pitch);
	for (int i = 0; i < mImageSize; i++)
	{
		((uint32_t*)TexturePixels)[i] = ColorToRGBA(mHDRBuffer[i]);
	}
	SDL_UnlockTexture(mTexture);
	SDL_RenderCopy(mRenderer, mTexture, &UpdateRect, &UpdateRect);
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

void Image::BrightPassFilter(Color * aBrightColorBuffer, double aThreshold)
{
	mLuminanceBuffer = new aq_float[mImageSize];
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			int p = y * mWidth + x;
			mLuminanceBuffer[p] = 0.2126 *  mHDRBuffer[p].x + 0.7152 * mHDRBuffer[p].y + 0.0722 * mHDRBuffer[p].z;
		}
	}

	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			int p = y * mWidth + x;
			aBrightColorBuffer[p] = mHDRBuffer[p] * mMiddleGrey / (mLuminanceBuffer[p] + 0.001);
			aBrightColorBuffer[p] *= (1.0 + (aBrightColorBuffer[p] / (aThreshold * aThreshold)));
			aBrightColorBuffer[p] -= 5.0;
			aBrightColorBuffer[p] = max(aBrightColorBuffer[p], 0.0);
			aBrightColorBuffer[p] /= (10.0 + aBrightColorBuffer[p]);
		}
	}
}
