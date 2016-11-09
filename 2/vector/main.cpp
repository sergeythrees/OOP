#include "stdafx.h"
#include <iostream>
#include <vector>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/copy.hpp>
#include "VectorProcessor.h"

using namespace std;
using namespace boost;
int main()
{
	cout << "Enter the elements of array with spaces\n";
	vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));

	ProcessVector(numbers);
	sort(numbers);
	
	cout.precision(4);
	copy(numbers, ostream_iterator<double>(cout, ", "));
	cout << endl;

	return 0;
}
