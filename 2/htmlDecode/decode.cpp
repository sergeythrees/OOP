#include "stdafx.h"
#include <vector>
#include <string>
#include "decode.h"

using namespace std;

const vector<pair<string, string>> dictionary = { { "&quot;", "\"" },{ "&apos;", "'" },{ "&lt;", "<" },{ "&gt;", ">" },{ "&amp;", "&" } };

string Decode(string &inputLine)
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