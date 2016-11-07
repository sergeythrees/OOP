#include "stdafx.h"
#include <vector>
#include <string>
#include "decode.h"

using namespace std;

string Decode(string &inputLine, vector<pair<string, string>> &dictionary)
{
	string result;

	for (size_t strPos = 0; strPos < inputLine.length(); ++strPos)
	{
		bool wasReplace = false;

		if (inputLine[strPos] == '&')
		{
			for (auto currentPair : dictionary)
			{
				if (currentPair.first == inputLine.substr(strPos, currentPair.first.length()))
				{
					result += currentPair.second;
					strPos += currentPair.first.length() - 1;
					wasReplace = true;
				}
			}
		}

		if (!wasReplace)
		{
			result += inputLine[strPos];
		}
	}
	return result;
}