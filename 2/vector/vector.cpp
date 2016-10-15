#include "stdafx.h"
#include <iostream>
#include <vector>
#include "VectorProcessor.h"

using namespace std;

int main()
{
	//vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));
	vector<double> numbers;
	//copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(numbers));
	
	while (!cin.eof())
	{
		double number;
		if (cin >> number)
			numbers.push_back(number);
		else
			break;
	}
	

	ProcessVector(numbers);

	for (auto number : numbers)
	{
		cout << number << ", ";
	}

	//copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, ", "));

	return 0;
}