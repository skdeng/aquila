#include "Image.h"

Image::Image()
{

}

Image::Image(const unsigned int aWidth, const unsigned int aHeight)
{
	mWidth = aWidth;
	mHeight = aHeight;
	mColorBuffer = new Color*[mHeight];
	for (unsigned int i = 0; i < mHeight; i++)
	{
		mColorBuffer[i] = new Color[mHeight];
	}
}

Image::~Image()
{
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
	}
}

void Image::Commit(const Sample& aSample, const Color aColor)
{
	mColorBuffer[(unsigned int)aSample.x][(unsigned int)aSample.y] = aColor;
}

void Image::DumpImage() const
{
	std::cout << "Image:" << std::endl;
	for (unsigned int y = 0; y < mHeight; y++)
	{
		for (unsigned int x = 0; x < mWidth; x++)
		{
			printf("(%1.1f,%1.1f,%1.1f) ", mColorBuffer[x][y].r, mColorBuffer[x][y].g, mColorBuffer[x][y].b);
		}
		std::cout << std::endl;
	}
}

Color** Image::GetBuffer() const
{
	return mColorBuffer;
}