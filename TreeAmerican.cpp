#include "TreeAmerican.h"

template <class T>

T max(T a, T b)
{
	return (a > b)? a : b;
}

TreeAmerican::TreeAmerican(double FinalTime, const PayOffBridge& ThePayOff_) : TreeProduct(FinalTime), ThePayOff(ThePayOff_)
{
}

TreeProduct* TreeAmerican::clone() const
{
	return new TreeAmerican(*this);
}
double TreeAmerican::FinalPayOff(double Spot) const
{
	return ThePayOff(Spot);
}

double TreeAmerican::PreFinalValue(double Spot, double, double DiscountedFutureValue) const
{
	return max(ThePayOff(Spot), DiscountedFutureValue);
}

