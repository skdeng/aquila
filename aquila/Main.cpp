#include "Sampler.h"

#include <iostream>

int main()
{
	Sampler sampler(16, 8);
	Sample* s = new Sample;
	while (sampler.GetSample(s))
	{
		std::cout << s->x << " " << s->y << std::endl;
	}
	delete s;
	return 0;
}