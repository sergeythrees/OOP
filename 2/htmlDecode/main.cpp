
#include "stdafx.h"
#include <iostream>
#include "Decode.h"

using namespace std;

void DecodeHtmlLines()
{
	string inputLine, cdf;
	
	while (getline(cin, inputLine))
		cout << Decode(inputLine) << endl;
}

int main()
{
	cout << "Enter the html lines\n";
	DecodeHtmlLines();
	cout << endl;

	return 0;
}