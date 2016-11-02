#include "stdafx.h"
#include <vector>
#include <string>
#include "decode.h"
#include "ReplaceSubString.h"

using namespace std;

string Decode(const string &inputLine, vector<pair<string, string>> &dictionary)
{
	string result(inputLine);
	for (auto currentPair : dictionary)
		ReplaceSubString(result, currentPair.first, currentPair.second);
	return result;
}