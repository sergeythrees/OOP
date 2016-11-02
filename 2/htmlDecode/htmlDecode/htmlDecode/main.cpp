
#include "stdafx.h"
#include <iostream>
#include <string>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/copy.hpp>
#include "htmlDecode.h"

using namespace std;
using namespace boost;
void ProcessInputLines()
{
	string inputLine;
	while (getline(cin,inputLine))
	{
		DecodeHtml(inputLine);
		cout << inputLine << endl;
	}
}
int main()
{
	cout << "Enter the html lines\n";
	ProcessInputLines();
	cout << endl;

	return 0;
}