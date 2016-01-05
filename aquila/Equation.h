#ifndef _AQ_UTILS_EQUATION_H_
#define _AQ_UTILS_EQUATION_H_

class Equation
{
public:
	Equation(double(*aFunction)(double));
	double Evaluate(double x);

	double Intergrate(double a, double b);

private:
	double (*mFunction) (double);

	static const int mIntegrationSample;
};

#endif