#include "Random.h"
#include <cstdlib>
#include <cmath>
#include "Normals.h"

// the basic math functions should be in namespace
// std but aren’t in VCPP6

#if !defined(_MSC_VER)
	using namespace std;
#endif

void RandomBase::GetGaussians(MJArray& variates)
{
	GetUniforms(variates);
	for (unsigned long i=0; i < Dimensionality; i++)
	{
		double x=variates[i];
		variates[i] = InverseCumulativeNormal(x);
	}
}

void RandomBase::ResetDimensionality(unsigned long NewDimensionality)
{
	Dimensionality = NewDimensionality;
}

RandomBase::RandomBase(unsigned long Dimensionality_) : Dimensionality(Dimensionality_)
{
}

double GetOneGaussianBySummation()
{
	double result=0.0;
	
	for(int j=0; j<12; j++)	result += rand()/static_cast<double>(RAND_MAX);
	result -= 6.0;
	
	return result;
}

double GetOneGaussianByBoxMuller()
{
	double result;
	double x, y, sizeSquared;
	
	do
	{
		x = 2.0*rand()/static_cast<double>(RAND_MAX)-1;
		y = 2.0*rand()/static_cast<double>(RAND_MAX)-1;
		sizeSquared = x*x + y*y;
	}
	while(sizeSquared >= 1.0);

	result = x*sqrt(-2*log(sizeSquared)/sizeSquared);
	
	return result;
}

