#include "stdafx.h"
#include <functional>
#include <iostream>
#include <vector>
#include <boost/range/algorithm/min_element.hpp>
#include "VectorProcessor.h"

using namespace std;

int main()
{
	vector<double> numbers;
	
	copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(numbers));

	ProcessVector(numbers, isless<double,double>, 
		      min_element<vector<double>::iterator>, multiplies<double>());

	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, ", "));

	return 0;
}
