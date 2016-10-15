#include "stdafx.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <boost/range/algorithm/transform.hpp>
#include <boost/phoenix.hpp>
#include "VectorProcessor.h"

using namespace std;
using namespace std::placeholders;
using namespace boost;
using boost::transform;
using namespace boost::phoenix;
using namespace boost::phoenix::placeholders;

void ProcessVector(std::vector<double> & numbers)
{
	sort(numbers.begin(), numbers.end());
	double minNumber =  *(numbers.begin());
	//auto Func = bind(multiplies<double>(), _1, minNumber);
	boost::transform(numbers, numbers.begin(), arg1 * minNumber);
}