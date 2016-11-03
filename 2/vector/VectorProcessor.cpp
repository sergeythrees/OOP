#include "stdafx.h"
#include <vector>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/phoenix.hpp>
#include "VectorProcessor.h"

using namespace boost;
using namespace boost::phoenix::placeholders;

void ProcessVector(std::vector<double> & numbers)
{
	if (numbers.size() != 0)
	{
		double minElement = *(min_element(numbers));
		boost::transform(numbers, numbers.begin(), arg1 * minElement);
	}
}
