
#include "stdafx.h"
#include <functional>
#include <iostream>
#include <vector>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/copy.hpp>
#include "htmlDecode.h"

using namespace std;
using namespace boost;
int main()
{
	cout << "Enter the elements of array with spaces\n";
	string inputLine(istream_iterator<char>(cin), (istream_iterator<char>()));

	//ProcessVector(numbers);

	cout << endl;

	return 0;
}