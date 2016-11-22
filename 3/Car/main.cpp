#include "stdafx.h"
#include "Car.h"
#include "CarControl.h"

using namespace std;

int main()
{
	CCar car;
	CCarControl carControl(car, cin, cout);

	cout << "Car and CarControl were initialized, please use these commands: " << endl
		<< "\tInfo - for print information of current car condition" << endl
		<< "\tEngineOn  - for turn on car engine" << endl
		<< "\tEngineOn  - for turn off car engine" << endl
		<< "\tSetGear <value> - for change engine gear" << endl
		<< "\tSetSpeed <value> - for change car speed" << endl
		<< "(This program is case-insensitive)" << endl
		<< endl;

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!carControl.HandleCommand())
		{
			cout << "Unknown command!\n";
		}
	}

	return 0;
}
