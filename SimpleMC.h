#ifndef SIMPLEMC_H
#define SIMPLEMC_H

#include "Vanilla.h"
#include "Parameters.h"
#include "Random.h"
#include "Statistics.h"

void SimpleMonteCarlo(	const VanillaOption& TheOption,
						double Spot,
						const Parameters& Vol,
						const Parameters& r,
						unsigned long NumberOfPaths,
						StatisticsMC& gatherer,
						RandomBase& generator);

#endif

