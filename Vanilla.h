#ifndef VANILLA_H
#define VANILLA_H

#include "PayOffBridge.h"

class VanillaOption
{
	private:
		double Expiry;
		
		PayOffBridge ThePayOff;
	
	public:
		VanillaOption(const PayOffBridge& ThePayOff_, double Expiry_);
		
		double GetExpiry() const;

		double OptionPayOff(double Spot) const;
};

#endif

