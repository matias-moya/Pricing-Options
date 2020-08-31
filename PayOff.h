#ifndef PAYOFF_H
#define PAYOFF_H

class PayOff
{
	public:
		PayOff(){}
		
		virtual double operator () (double Spot) const=0;
		
		virtual ~PayOff(){}
		
		virtual PayOff* clone() const=0;
};


class PayOffCall : public PayOff
{
	private:
		double Strike;
	
	public:
		PayOffCall(double Strike_);
		
		virtual double operator () (double Spot) const;

		virtual ~PayOffCall(){}
		
		virtual PayOff* clone() const;
};


class PayOffPut : public PayOff
{
	private:
		double Strike;
	
	public:
		PayOffPut(double Strike_);

		virtual double operator () (double Spot) const;

		virtual ~PayOffPut(){}
		
		virtual PayOff* clone() const;
};

#endif

