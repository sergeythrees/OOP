#include "stdafx.h"
#include "CMyArray.h"

using namespace std;

int main()
{
	string inputLine;
	CMyArray<string> stringArray;
	cout << "Please input lines (Ctrl-Z to finish):" << endl;
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
	cin.clear();
	double inputNumber;
	CMyArray<double> numbersArray;
	cout << "Please input numbers (Ctrl-Z to finish):" << endl;
	while (cin >> inputNumber)
	{
		numbersArray.Append(inputNumber);
	}
	for (auto it = numbersArray.begin(); it != numbersArray.end(); ++it)
	{
		cout << *it << endl;
	}
	cout << endl;
	for (auto it = numbersArray.rbegin(); it != numbersArray.rend(); ++it)
	{
		cout << *it << endl;
	}
	return 0;
}

