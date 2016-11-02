
#include "stdafx.h"
#include <iostream>
#include "Decode.h"

using namespace std;

void DecodeHtmlLines()
{
	string inputLine;
	map<string, string> htmlMap = { { "&quot;", "\"" }, { "&apos;", "'" }, { "&lt;", "<" }, { "&gt;", ">" }, { "&amp;", "&" } };

	while (getline(cin, inputLine))
		cout << Decode(inputLine, htmlMap) << endl;
}

int main()
{
	cout << "Enter the html lines\n";
	DecodeHtmlLines();
	cout << endl;

	return 0;
}