template<class T>

double Bisection(double Target, double Low, double High, double Tolerance, T TheFunction)
{
	double x=0.5*(Low+High);
	double y=TheFunction(x);

	do
	{
		//cout << Low << " " << High << endl;	
		if (y < Target)	Low=x;
		
		if (y > Target)	High = x;

		x = 0.5*(Low+High);
		y = TheFunction(x);
	}
	while( (fabs(y-Target) > Tolerance) );

	return x;
}



