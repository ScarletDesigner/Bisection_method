#include <iostream>
#include <fstream>
#include <conio.h>
#include <cmath>
using namespace std;
const int numberOfFactors = 4;
float factors[numberOfFactors];
float begin, end;
const float epsilon = 0.000001;

float function(float factors[numberOfFactors], float x)
{
	float sum=0;
	for(int i=0; i<numberOfFactors; i++)
	{
		int lastFactor = numberOfFactors - 1;
		sum = sum * x + factors[lastFactor - i];
	}
	return sum;
}
float bisection(float factors[numberOfFactors], float a, float b)
{	
	float s = (a + b) / 2.0;
	float Begin = function(factors,a);
	float End = function(factors,b);
	float Center = function(factors,s);
	if (Center == 0)
		return s;

	float precision = fabs(a - b);
	if(epsilon > precision)
		return a;
	
	bool hasZeroInFirstHalf = (Begin * Center <= 0);
	bool hasZeroInSeconHalf = (Center * End <= 0);
	if(hasZeroInFirstHalf)
		return bisection(factors, a, s);
	if(hasZeroInSeconHalf)
		return bisection(factors, s, b);
	
}
int main(){
	
	fstream file("function.txt");
	if(file.good()==false)
	{
		cout<<"Failed to load the file"<<endl;
		exit(0);
	}

	file >> begin;
	file >> end;
	for(int i=0; i<numberOfFactors; i++)
	{
		float factor;
		file >> factor;
		factors[i] = factor;
	}
	file.close();
	cout<<bisection(factors, begin, end);
	getch();
	return 0;
}
