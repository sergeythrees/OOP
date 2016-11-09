#include "stdafx.h"
#include <vector>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/transform.hpp>
#include "VectorProcessor.h"

using namespace std;
using namespace boost;

double RoundToThree(double number)
{
	return trunc(number * 1000.0) / 1000.0;
}
void ProcessVector(vector<double> & numbers)
{
	if (numbers.size() != 0)
	{
		double minElement = *(min_element(numbers));
		boost::transform(numbers, numbers.begin(), 
			[minElement](double number) 
			{ return RoundToThree(number*minElement);  });
	}
}
