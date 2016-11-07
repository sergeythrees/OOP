#include "stdafx.h"
#include <vector>
#include <string>
#include "decode.h"

using namespace std;

const vector<pair<string, string>> htmlEntities = { { "&quot;", "\"" },{ "&apos;", "'" },{ "&lt;", "<" },{ "&gt;", ">" },{ "&amp;", "&" } };

string DecodeHtmlText(string const& html)
{
	string result;

	for (size_t readPos = 0; readPos < html.length(); ++readPos)
	{

		bool wasReplace = false;

		if (html[readPos] == '&')
		{
			for (auto currentPair : htmlEntities)
			{
				if (currentPair.first == html.substr(readPos, currentPair.first.length()))
				{
					result.append(currentPair.second);
					readPos += currentPair.first.length() - 1;
					wasReplace = true;
				}
			}
		}

		if (!wasReplace)
		{
			result += html[readPos];
		}
	}
	return result;
}