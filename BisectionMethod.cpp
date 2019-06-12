#include <iostream>
#include <fstream>
#include <conio.h>
#include <cmath>
using namespace std;

class FileLoader
{
protected:
	fstream file;
	float start, end;
	static const int numberOfFactors = 4;
	float factors[numberOfFactors];

public:
	void loadFile(string fileName)
	{
		file.open(fileName.c_str());
		checkIfFileExists();
		loadBoundaryOfFunction();
		loadFactors();
		file.close();
	}
private:
	void checkIfFileExists()
	{
		if(file.good() == false)
		{
			cout<<"Failed to load the file"<<endl;
			exit(0);
		}
	}
	
	void loadBoundaryOfFunction()
	{
		file >> start;
		file >> end;
	}
	
	void loadFactors()
	{
		for(int i=0; i<numberOfFactors; i++)
		{
			float factor;
			file >> factor;
			factors[i] = factor;
		}
	}
};

class ZeroFinder: public FileLoader
{
	static const float epsilon = 0.000001;
	
public:	
	void printZeroOfFunction()
	{
		float precision = fabs(start - end);
		float center;
		while(epsilon < precision)
		{
			precision = fabs(start - end);
			center = (start + end) / 2.0;
			float startValue = getValue(start);
			float endValue = getValue(end);
			float centerValue = getValue(center);
			if (centerValue == 0)
			{
				cout<<center<<endl;
				exit(0);
			}
	
			bool hasZeroInFirstHalf = (startValue * centerValue <= 0);
			bool hasZeroInSecondHalf = (centerValue * endValue <= 0);
			
			if(hasZeroInFirstHalf)
				end = center;
				
			if(hasZeroInSecondHalf)
				start = center;
		}
		cout<<center<<endl;
	}
private:
	float getValue(float x)
	{
		float sum=0;
		for(int i=0; i<numberOfFactors; i++)
		{
			int lastFactor = numberOfFactors - 1;
			sum = sum * x + factors[lastFactor - i];
		}
		return sum;
	}
	

};

int main(){
	
	ZeroFinder a;
	a.loadFile("function.txt");
	a.printZeroOfFunction();
	
	return 0;
}
