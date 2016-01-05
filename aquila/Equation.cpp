#include "Equation.h"
#include <random>

const int Equation::mIntegrationSample = 100;

Equation::Equation(double(*aFunction)(double))
{
	mFunction = aFunction;
}

double Equation::Evaluate(double x)
{
	return mFunction(x);
}

double Equation::Intergrate(double a, double b)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::normal_distribution<> N(0, 1);

	double Integral = 0.0;
	for (int i = 0; i < mIntegrationSample; i++)
	{

	}
	return Integral;
}
