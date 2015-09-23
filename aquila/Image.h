#ifndef _AQUILA_IMAGE_H_
#define _AQUILA_IMAGE_H_

#include "Common.h"

#ifdef _WIN32 
#include <Windows.h>
#endif

class Image
{
public:
	Image();
	Image(const unsigned int aWidth, const unsigned int aHeight);
	~Image();
	
	void Commit(const Sample& aSample, const Color aColor);

#ifdef AQ_DEBUG
	void DumpImage() const;
	Color** GetBuffer() const;
#endif

private:
	//private member functions
	void InitBufferInfo();
	
private:
	Color** mColorBuffer;

	unsigned int mWidth;
	unsigned int mHeight;

#ifdef _WIN32
public:
	void SwapBuffer(HDC ahDC);
private:
	BYTE* mWinBuffer;
	BYTE* GetWinBuffer();
	BITMAPINFO mColorBufferInfo;
#endif
};

#endif