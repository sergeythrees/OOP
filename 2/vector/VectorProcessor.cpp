#include "stdafx.h"
#include <vector>
#include <functional>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/transform.hpp>
#include "VectorProcessor.h"

using namespace std;
using namespace std::placeholders;
using namespace boost;

void ProcessVector(vector<double> & numbers)
{
	if (numbers.size() != 0)
	{
		double minElement = *(min_element(numbers));
		boost::transform(numbers, numbers.begin(), 
			bind(multiplies<double>(), _1, minElement));
	}
}
