#ifndef PAYOFFBRIDGE_H
#define PAYOFFBRIDGE_H

#include "PayOff.h"

class PayOffBridge
{
	private:
		PayOff* ThePayOffPtr;
	
	public:
		PayOffBridge(const PayOffBridge& original);
	
		PayOffBridge(const PayOff& innerPayOff);

		inline double operator()(double Spot) const;

		~PayOffBridge();

		PayOffBridge& operator=(const PayOffBridge& original);
};

inline double PayOffBridge::operator()(double Spot) const
{
	return ThePayOffPtr->operator()(Spot);
}

#endif

