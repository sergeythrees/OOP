#include "stdafx.h"
#include "ProcessErrors.h"

bool IsValidArgumentsCount(int argumensCount)
{
	if (argumensCount != MAX_NUM_OF_ARGUMENTS)
	{
		cout << "Wrong arguments count\n"
			<< "Usage: miniDictionary.exe <input file>\n";
		return false;
	}

	return true;
}