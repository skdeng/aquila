#include "Sampler.h"
#include "Camera.h"
#include "Raytracer.h"
#include "Image.h"
#include "Wnd.h"

#include <iostream>

int main()
{
	Sampler sp;
	Camera cam(vec3(0,0,5), vec3(0,0,-1), vec3(0,1,0), 45.0f, CONSTANT::IMAGE_WIDTH, CONSTANT::IMAGE_HEIGHT);
	Raytracer rt;
	Image image(CONSTANT::IMAGE_WIDTH, CONSTANT::IMAGE_HEIGHT);
	Wnd Window;
	Sample s;
	while (sp.GetSample(&s))
	{
		Ray r;
		Color c;
		cam.GetRay(s, &r);
		rt.Trace(r, 0, &c);
		image.Commit(s, c);
	}

	image.DumpImage();

	int tmp;
	std::cin >> tmp;
	return 0;
}