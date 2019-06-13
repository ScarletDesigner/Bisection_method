#include <iostream>
#include <fstream>
#include <conio.h>
#include <cmath>
#include <vector>
using namespace std;

class FileLoader
{
protected:
	fstream file;
	float start, end;
	int numberOfFactors;
	vector<float> factors;

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
		numberOfFactors = 0;
		float factor;
		while(file >> factor)
		{
			numberOfFactors++;
			factors.push_back(factor);
		}
	}
};

class ZeroFinder: public FileLoader
{
	static const float epsilon = 0.000001; 
	float precision;
	float center;
	float startValue, endValue, centerValue;
	
public:	
	void printZeroOfFunction()
	{
		precision = fabs(start - end);
		
		while(epsilon < precision)
			findZero();
		
		cout<<center<<endl;
	}
private:
	
	void findZero()
	{
		initializeStartingVariables();
		hasInfiniteAmmountOfZeros();
		hasZeroInCenter();
		hasZeroInFirstHalf();
		hasZeroInSecondHalf();
	}
	
	void initializeStartingVariables()
	{
		precision = fabs(start - end);
		center = (start + end) / 2.0;
		startValue = getValue(start);
		endValue = getValue(end);
		centerValue = getValue(center);
	}
	
	void hasInfiniteAmmountOfZeros()
	{
		if(startValue == 0 && centerValue == 0 && endValue == 0 )
		{
			cout<<"Function is linear and has infinite ammount of zeros"<<endl;
			exit(0);
		}
	}
	
	void hasZeroInFirstHalf()
	{
		if(startValue * centerValue <= 0)
			end = center;
	}
	
	void hasZeroInSecondHalf()
	{
		if(centerValue * endValue <= 0)
			start = center;
	}
	
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
	
	void hasZeroInCenter()
	{
		if (centerValue == 0)
		{
			cout<<center<<endl;
			exit(0);
		}
	}

};

int main(){
	
	ZeroFinder a;
	a.loadFile("function1.txt");
	a.printZeroOfFunction();
	
	return 0;
}
