#include "stdafx.h"
#include <string>
#include <vector>
#include "htmlDecode.h"
#include <boost/algorithm/searching/knuth_morris_pratt.hpp>

using namespace std;
using namespace boost;
using namespace boost::algorithm;

string::size_type KMP_Search(const string& S, int begin, const string& pattern){
	vector<int> pf(pattern.length());

	pf[0] = 0;
	for (int k = 0, i = 1; i<pattern.length(); ++i){
		while (k>0 && pattern[i] != pattern[k])
			k = pf[k - 1];

		if (pattern[i] == pattern[k])
			k++;

		pf[i] = k;
	}

	for (int k = 0, i = begin; i<S.length(); ++i){
		while ((k>0) && (pattern[k] != S[i]))
			k = pf[k - 1];

		if (pattern[k] == S[i])
			k++;

		if (k == pattern.length())
			return (i - pattern.length() + 1);//либо продолжаем поиск следующих вхождений
	}

	return (string::npos);
}

size_t ReplaceSubString(string &inputLine, const string &searchString, const string &replaceString)
{
	if (searchString == replaceString)
		return 0;

	size_t foundPosition = inputLine.find(searchString);
	if (foundPosition == inputLine.npos)
		return 0;

	size_t currentPosition = 0;
	size_t numberOfReplacements = 0;
	string result;
	result.reserve(inputLine.length());

	while (foundPosition != inputLine.npos)
	{
		result.append(inputLine, currentPosition, foundPosition - currentPosition);
		result += replaceString;
		currentPosition = foundPosition + searchString.length();
		foundPosition = inputLine.find(searchString, currentPosition);
		++numberOfReplacements;
	}
	inputLine = result.append(inputLine, currentPosition, inputLine.length() - currentPosition);

	return numberOfReplacements;
}

void DecodeHtml(string &inputLine)
{
	ReplaceSubString(inputLine, "&quot;", "\""); 
	ReplaceSubString(inputLine, "&apos;", "'");
	ReplaceSubString(inputLine, "&lt;", "<");
	ReplaceSubString(inputLine, "&gt;", ">");
	ReplaceSubString(inputLine, "&amp;", "&");
}