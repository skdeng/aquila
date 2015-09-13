#ifndef _AQUILA_MATERIAL_H_
#define _AQUILA_MATERIAL_H_

#include "Common.h"

class Material
{
public:
	void GetBRDF(const LocalGeo& aLocal, BRDF* aBRDF);

private:
	BRDF ConstBRDF;
};

#endif