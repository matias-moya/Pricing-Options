#ifndef PAYOFF_FACTORY_H
#define PAYOFF_FACTORY_H

#include "PayOff.h"

#include <map>
#include <string>

class PayOffFactory
{
	public:
		typedef PayOff* (*CreatePayOffFunction)(double);
		
		static PayOffFactory& Instance();

		void RegisterPayOff(std::string, CreatePayOffFunction);

		PayOff* CreatePayOff(std::string PayOffId, double Strike);

		~PayOffFactory(){};

	private:
		std::map<std::string,CreatePayOffFunction> TheCreatorFunctions;

		PayOffFactory(){}

		PayOffFactory(const PayOffFactory&){}

		PayOffFactory& operator = (const PayOffFactory&)
		{ return *this;}
};
#endif

