#include "Image.h"

Image::Image(SDL_Renderer* aRenderer, const unsigned int aWidth, const unsigned int aHeight)
{
	mWidth = aWidth;
	mHeight = aHeight;
	mRenderer = aRenderer;
	mTexture = SDL_CreateTexture(aRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);
}

Image::~Image()
{
	SDL_DestroyTexture(mTexture);
}

void Image::Commit(const Sample& aSample, const Color& aColor)
{
	SDL_Rect UpdateRect;
	UpdateRect.x = (int)aSample.x;
	UpdateRect.y = (int)aSample.y;
	UpdateRect.w = UpdateRect.h = 1;
	int pitch;

	void* TexturePixels;
	SDL_LockTexture(mTexture, &UpdateRect, &TexturePixels, &pitch);
	*((uint32_t*)TexturePixels) = ColorToRGBA(aColor);
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

uint32_t Image::ColorToRGBA(const Color& aColor)
{
	uint32_t rgba = 0;
	rgba += ((unsigned int)(aColor.r * 0xFF)) << 24;
	rgba += ((unsigned int)(aColor.g * 0xFF)) << 16;
	rgba += ((unsigned int)(aColor.b * 0xFF)) << 8;
	rgba += 0xFF;
	return rgba;
}