#include <iostream>
#include <fstream>
#include <conio.h>
#include <cmath>
using namespace std;
// example function:  -1 + 1.14833*x -51.59809*x*x + 224.47368*x*x*x
// where 0 <= x <= 1
const int numberOfFactors = 4;
float factors[numberOfFactors];
float xBegin, xEnd;
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
	float precision = fabs(a - b);
	if(epsilon > precision)
		return a;
	float s = (a + b) / 2.0;
	bool hasZeroPlacedInFirstHalf = (function(factors, a) * function(factors, s) <= 0);
	bool hasZeroPlacedInSeconHalf = (function(factors, s) * function(factors, b) <= 0);
	if(hasZeroPlacedInFirstHalf)
		return bisection(factors, a, s);
	if(hasZeroPlacedInSeconHalf)
		return bisection(factors, s, b);
	
}
int main(){
	
	fstream file("function.txt");
	if(file.good()==false)
	{
		cout<<"Failed to load the file"<<endl;
		exit(0);
	}

	file >> xBegin;
	file >> xEnd;
	for(int i=0; i<numberOfFactors; i++)
	{
		float factor;
		file >> factor;
		factors[i] = factor;
	}
	file.close();
	cout<<bisection(factors, xBegin, xEnd);
	getch();
	return 0;
}
