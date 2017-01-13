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

	cout << endl << "Print by means of - range based for:" << endl;
	for (auto current:stringArray)
	{
		cout << current << endl;
	}

	cout << endl << "Print by means of - std::for_each algorythm:" << endl;
	for_each(stringArray.begin(), stringArray.end(), 
		[&](const auto& current)
		{
		cout << current << endl;
		});

	cout << endl << "Print by means of - range based for(recursive):" << endl;
	for (auto it = stringArray.rbegin(); it != stringArray.rend(); ++it)
	{
		cout << *it << endl;
	}

	cout << endl << "Print by means of - std::for_each algorythm(recursive):" << endl;
	for_each(stringArray.rbegin(), stringArray.rend(),
		[&](const auto& current)
	{
		cout << current << endl;
	});
	cin.clear();

	double inputNumber;
	CMyArray<double> numbersArray;
	cout << endl << "Please input numbers (Ctrl-Z to finish):" << endl;
	while (cin >> inputNumber)
	{
		numbersArray.Append(inputNumber);
	}
	
	cout << endl << "Print by means of - range based for:" << endl;
	for (auto current : numbersArray)
	{
		cout << current << endl;
	}

	cout << endl << "Print by means of - std::for_each algorythm:" << endl;
	for_each(numbersArray.begin(), numbersArray.end(),
		[&](const auto& current)
	{
		cout << current << endl;
	});

	cout << endl << "Print by means of - range based for(recursive):" << endl;
	for (auto it = numbersArray.rbegin(); it != numbersArray.rend(); ++it)
	{
		cout << *it << endl;
	}

	cout << endl << "Print by means of - std::for_each algorythm(recursive):" << endl;
	for_each(numbersArray.rbegin(), numbersArray.rend(),
		[&](const auto& current)
	{
		cout << current << endl;
	});
	cin.clear();
	return 0;
}

