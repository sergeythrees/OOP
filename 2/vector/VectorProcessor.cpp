#include "stdafx.h"
#include <vector>
#include <functional>
#include <boost/range/algorithm/transform.hpp>
#include <boost/phoenix.hpp>
#include <boost/range/algorithm/sort.hpp>
#include "VectorProcessor.h"

using namespace std;
using namespace std::placeholders;
using namespace boost;
using boost::transform;
using boost::sort;
using boost::min_element;


void ProcessVector(std::vector<double> & numbers, 
	std::function<bool(double a, double b)> PredicateFunc, 
	std::function<vector<double>::iterator(vector<double>::iterator, vector<double>::iterator)> SearchFunc,
	std::function<double(double a, double b)> TransformFunc)
{
	sort(numbers, PredicateFunc);
	double foundNumber = *SearchFunc(numbers);
	transform(numbers, numbers.begin(), bind(TransformFunc, _1, foundNumber));
}
