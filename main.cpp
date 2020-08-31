#include "SimpleMC.h"
#include <iostream>
#include "Vanilla.h"
#include "Parameters.h"
#include "Statistics.h"
#include "ConvergenceTable.h"
#include "ParkMiller.h"
#include "AntiThetic.h"
#include "PathDependentAsian.h"
#include "ExoticBSEngine.h"
#include "BinomialTree.h"
#include "TreeAmerican.h"
#include "TreeEuropean.h"
#include "BlackScholesFormulas.h"
#include "PayOffForward.h"
#include <cmath>
#include "Bisection.h"
#include "BSCallClass.h"
#include "NewtonRaphson.h"
#include "BSCallTwo.h"
#include "PayOffConstructible.h"
#include "PayOffBridge.h"
#include "PayOffFactory.h"
#include <string>

using namespace std;

int main()
{
	double Expiry, Strike, Spot, Vol,  r, d;
	unsigned long NumberOfPaths, Steps;
	unsigned NumberOfDates;

	cout << "Enter expiry" << endl;		cin >> Expiry;
	cout << "Enter strike" << endl;		cin >> Strike;
	cout << "Enter spot" << endl;		cin >> Spot;
	cout << "Enter vol" << endl;		cin >> Vol;
	cout << "r" << endl;				cin >> r;
	cout << "Number of paths" << endl;	cin >> NumberOfPaths;

	ParametersConstant VolParam(Vol);
	ParametersConstant rParam(r);

	PayOffCall callPayOff(Strike);
	PayOffPut putPayOff(Strike);

	VanillaOption callOption(callPayOff, Expiry);
	VanillaOption putOption(putPayOff, Expiry);

	StatisticsMean gathererCall;
	StatisticsMean gathererPut;

	ConvergenceTable gathererCallCT(gathererCall);
	ConvergenceTable gathererPutCT(gathererPut);

	RandomParkMiller generatorCall(1);
	RandomParkMiller generatorPut(1);

	AntiThetic GenAntiTCall(generatorCall);
	AntiThetic GenAntiTPut(generatorPut);

	SimpleMonteCarlo(	callOption,
						Spot,
						VolParam,
						rParam,
						NumberOfPaths,
						gathererCallCT,
						GenAntiTCall);
											
	SimpleMonteCarlo(	putOption,
						Spot,
						VolParam,
						rParam,
						NumberOfPaths,
						gathererPutCT,
						GenAntiTPut);
							
	cout << "Then  ... " << endl;
											
	cout <<"The prices are:" << endl;

	vector<vector<double> > resultsCall = gathererCallCT.GetResultsSoFar();
	
	for(int i=0; i < resultsCall.size(); i++){
		for(int j=0; j < resultsCall[i].size(); j++){
			cout << resultsCall[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "(It should be " << BlackScholesCall(Spot,Strike,r,0,Vol,Expiry) << ") \n for the call and: \n"; 

	vector<vector<double> > resultsPut = gathererPutCT.GetResultsSoFar();
	
	for(int i=0; i < resultsPut.size(); i++){
		for(int j=0; j < resultsPut[i].size(); j++){
			cout << resultsPut[i][j] << " ";
		}
		cout << endl;
	}

	cout << " for the put" << endl;

	cout << "Now we price an arithmetic asian call option with the same expiry, strike, spot, vol, r and number of paths. We need \"d\" and the number of dates" << endl;
	
	cout << "\nd\n";
	cin >> d;
	
	cout << "Number of dates\n";
	cin >> NumberOfDates;

	MJArray times(NumberOfDates);

	for (unsigned long i=0; i < NumberOfDates; i++)
		times[i] = (i+1.0)*Expiry/NumberOfDates;

	ParametersConstant dParam(d);
	PathDependentAsian theOption(times, Expiry, callPayOff);

	StatisticsMean gatherer;
	ConvergenceTable gathererTwo(gatherer);
	RandomParkMiller generator(NumberOfDates);
	AntiThetic GenTwo(generator);

	ExoticBSEngine theEngine(theOption,rParam, dParam, VolParam, GenTwo, Spot);
	theEngine.DoSimulation(gathererTwo, NumberOfPaths);

	vector<vector<double> > results = gathererTwo.GetResultsSoFar();

	cout <<"\nFor the Asian call price the results are \n";
	
	for (unsigned long i=0; i < results.size(); i++)
	{
		for (unsigned long j=0; j < results[i].size(); j++)
			cout << results[i][j] << " ";
		cout << "\n";
	}
	
	cout << "We evaluate european and american options by using a tree with the same parameters as before." << endl;
	
	cout << "Steps\n";
	cin >> Steps;
	
	TreeEuropean europeanOption(Expiry, callPayOff);
	TreeAmerican americanOption(Expiry, callPayOff);
	SimpleBinomialTree theTree(Spot, rParam, dParam, Vol, Steps, Expiry);

	double euroPrice = theTree.GetThePrice(europeanOption);
	double americanPrice = theTree.GetThePrice(americanOption);
	cout << "euro price" << euroPrice << "amer price" << americanPrice << "\n";
	
	double BSPrice = BlackScholesCall(Spot,Strike,r,d,Vol,Expiry);
	cout << "BS formula euro price" << BSPrice << "\n";

	PayOffForward forwardPayOff(Strike);
	TreeEuropean forward(Expiry,forwardPayOff);
	double forwardPrice = theTree.GetThePrice(forward);
	cout << "forward price by tree" << forwardPrice << "\n";
	double actualForwardPrice = exp(-r*Expiry)*(Spot*exp((r-d)*Expiry)-Strike);

	cout << "forward price" << actualForwardPrice << "\n";
	Steps++; // now redo the trees with one more step
	SimpleBinomialTree theNewTree(Spot, rParam, dParam, Vol, Steps, Expiry);

	double euroNewPrice = theNewTree.GetThePrice(europeanOption);
	double americanNewPrice = theNewTree.GetThePrice(americanOption);
	cout << "euro new price" << euroNewPrice << "amer new price" << americanNewPrice << "\n";
	double forwardNewPrice = theNewTree.GetThePrice(forward);
	cout << "forward price by new tree" << forwardNewPrice << "\n";

	double averageEuro = 0.5*(euroPrice+euroNewPrice);
	double averageAmer = 0.5*(americanPrice+americanNewPrice);
	double averageForward = 0.5*(forwardPrice+forwardNewPrice);

	cout << "euro av price" << averageEuro << "amer av price" << averageAmer << "\n";
	cout << "av forward" << averageForward << "\n";
	
	cout << "Finally, the inverse of BS to get the implied volatility" << endl;

	double Price;
	cout << "\nEnter price\n";
	cin >> Price;

	double low,high;
	cout << "\nlower guess\n";
	cin >> low;

	cout << "\nhigh guess\n";
	cin >> high;

	double tolerance;
	cout << "\nTolerance\n";
	cin >> tolerance;

	BSCall theCall(r, d, Expiry, Spot, Strike);

	double ImpliedVol = Bisection(Price,low,high,tolerance,theCall);
	double PriceTwo = BlackScholesCall(Spot, Strike, r, d, ImpliedVol, Expiry);

	cout << "\n vol " << ImpliedVol << " pricetwo " << PriceTwo << "\n";

	cout << "With Newtos Raphson we obtain the following: \n";
	
	double start;
	cout << "\nstart guess\n";
	cin >> start;

	BSCallTwo theCallTwo(r,d,Expiry,Spot,Strike);

	ImpliedVol = NewtonRaphson<BSCallTwo,&BSCallTwo::Price, &BSCallTwo::Vega>(Price, start, tolerance, theCallTwo);
	PriceTwo = BlackScholesCall(Spot,Strike,r,d,ImpliedVol,Expiry);

	cout << "\n vol " << ImpliedVol << " \nprice two:" << PriceTwo << "\n";

	std::string name;
	
	cout << "\npay-off name\n";
	cin >> name;

	PayOff* PayOffPtr = PayOffFactory::Instance().CreatePayOff(name,Strike);
	if (PayOffPtr != NULL)
	{
		cout << "\n" << PayOffPtr->operator()(Spot) << "\n";
		delete PayOffPtr;
	}


	return 0;
}

