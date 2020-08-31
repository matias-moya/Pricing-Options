#include "PayOff.h"
#include <algorithm>

using namespace std;

PayOffCall::PayOffCall(double Strike_) : Strike(Strike_)
{
}

double PayOffCall::operator () (double Spot) const
{
	return max(Spot-Strike,0.0);
}

PayOff* PayOffCall::clone() const
{
	return new PayOffCall(*this);
}

PayOffPut::PayOffPut(double Strike_) : Strike(Strike_)
{
}

double PayOffPut::operator () (double Spot) const
{
	return max(Strike-Spot,0.0);
}

PayOff* PayOffPut::clone() const
{
	return new PayOffPut(*this);
}
