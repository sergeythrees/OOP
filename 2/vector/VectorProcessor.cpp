#include "stdafx.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <boost/range/algorithm/transform.hpp>
#include <boost/phoenix.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include "VectorProcessor.h"

using namespace std;
using namespace std::placeholders;
using namespace boost;
using boost::transform;
using boost::sort;
using boost::min_element;

//bool IsLess(double a, double b)
//{
//	return a < b;
//}
void ProcessVector(std::vector<double> & numbers, 
	std::function<bool(double a, double b)> PredicateFunc, 
	std::function<auto(vector<double>)> SearchFunc,
	std::function<double(double a, double b)> TransformFunc)
{
	sort(numbers, PredicateFunc);
	double minNumber = *SearchFunc(numbers);
	//double minNumber = 
		//*SearchElementFunc(numbers.begin(),numbers.end());
	//double minNumber =  *(numbers.begin());
	transform(numbers, numbers.begin(), bind(TransformFunc, _1, minNumber));
}