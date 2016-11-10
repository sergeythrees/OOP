#include "stdafx.h"
#include "DictionaryFunctions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

bool HasUserAgreed(string question)
{
	cout << question << endl;

	string answer;

	cin >> answer;
	if (answer == "Y" || answer == "y")
	{
		return true;
	}

	return false;
}

