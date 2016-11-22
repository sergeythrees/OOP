#include "stdafx.h"
#include "Car.h"
#include "CarControl.h"

using namespace std;

int main()
{
	CCar car;
	CCarControl carControl(car, cin, cout);

	cout << "Car and CarControl were initialized, please use these commands: " << endl
		<< "Info - for print information of current car condition" << endl
		<< "EngineOn  - for turn on car engine" << endl
		<< "EngineOn  - for turn off car engine" << endl
		<< "SetGear <value> - for change engine gear" << endl
		<< "SetSpeed <value> - for change car speed" << endl;
	cout << endl;

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
