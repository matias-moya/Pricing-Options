#if !defined(STATISTICS)
#define STATISTICS

#include <vector>

class StatisticsMC
{
	public:
		StatisticsMC(){}

		virtual void DumpOneResult(double result)=0;

		virtual std::vector<std::vector<double> > GetResultsSoFar() const=0;
		
		virtual StatisticsMC* clone() const=0;

		virtual ~StatisticsMC(){}
};

class StatisticsMean : public StatisticsMC
{
	private:
		double RunningSum;

		unsigned long PathsDone;
	
	public:
		StatisticsMean();

		virtual void DumpOneResult(double result);

		virtual std::vector<std::vector<double> > GetResultsSoFar() const;

		virtual StatisticsMC* clone() const;
};

#endif

