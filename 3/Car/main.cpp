#include "stdafx.h"
#include "Car.h"
#include "CarControl.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	CCar car;
	CCarControl carControl(car, cin, cout);

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
