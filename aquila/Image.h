#ifndef _AQUILA_IMAGE_H_
#define _AQUILA_IMAGE_H_

#include "Common.h"

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
	Color** mColorBuffer;
	unsigned int mWidth;
	unsigned int mHeight;
};

#endif