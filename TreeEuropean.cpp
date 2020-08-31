#include "TreeEuropean.h"

TreeEuropean::TreeEuropean(double FinalTime, const PayOffBridge& ThePayOff_) : TreeProduct(FinalTime), ThePayOff(ThePayOff_)
{
}

double TreeEuropean::FinalPayOff(double Spot) const
{
	return ThePayOff(Spot);
}

double TreeEuropean::PreFinalValue(double, double, double DiscountedFutureValue) const
{
	return DiscountedFutureValue;
}

TreeProduct* TreeEuropean::clone()const
{
	return new TreeEuropean(*this);
}

