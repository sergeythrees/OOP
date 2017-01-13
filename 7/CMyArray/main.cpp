#include "stdafx.h"
#include "CMyArray.h"

using namespace std;

int main()
{
	string inputLine;
	CMyArray<string> stringArray;
	while (cin >> inputLine)
	{
		stringArray.Append(inputLine);
	}
	for (auto it = stringArray.begin(); it != stringArray.end(); ++it)
	{
		cout << *it << endl;
	}
	cout << endl;
	for (auto it = stringArray.rbegin(); it != stringArray.rend(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}

