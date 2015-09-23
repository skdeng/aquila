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
		mColorBuffer = nullptr;
	}
}

void Image::Commit(const Sample& aSample, const Color aColor)
{
	mColorBuffer[(unsigned int)aSample.x][(unsigned int)aSample.y] = aColor;
}

void Image::InitBufferInfo()
{
#ifdef _WIN32
	memset(&mColorBufferInfo, 0, sizeof(BITMAPINFOHEADER));
	mColorBufferInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	mColorBufferInfo.bmiHeader.biPlanes = 1;
	mColorBufferInfo.bmiHeader.biBitCount = 24;
	mColorBufferInfo.bmiHeader.biCompression = BI_RGB;
	mColorBufferInfo.bmiHeader.biWidth = mWidth;
	mColorBufferInfo.bmiHeader.biHeight = mHeight;
#endif
}

#ifdef _WIN32
void Image::SwapBuffer(HDC ahDC)
{
	if (mColorBuffer != nullptr)
	{
		BYTE* WinBuffer = GetWinBuffer();
		StretchDIBits(ahDC, 0, 0, mWidth, mHeight, 0, 0, mWidth, mHeight, GetWinBuffer(), &mColorBufferInfo, DIB_RGB_COLORS, SRCCOPY);
	}
}
BYTE* Image::GetWinBuffer()
{
	if ()
	BYTE* itr;
	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			itr = Buffer + (mWidth * j + i) * 3;
			itr[0] = mColorBuffer[i][j].r;
			itr[1] = mColorBuffer[i][j].g;
			itr[2] = mColorBuffer[i][j].b;
		}
	}
	return Buffer;
}
#endif

#ifdef AQ_DEBUG
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
#endif