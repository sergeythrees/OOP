#include "stdafx.h"
#include <string>
#include <vector>

using namespace std;

string::size_type KMP_Search(const string& S, size_t begin, const string& pattern){
	vector<size_t> pf(pattern.length());

	pf[0] = 0;
	for (size_t k = 0, i = 1; i<pattern.length(); ++i){
		while (k>0 && pattern[i] != pattern[k])
			k = pf[k - 1];

		if (pattern[i] == pattern[k])
			k++;

		pf[i] = k;
	}

	for (size_t k = 0, i = begin; i<S.length(); ++i){
		while ((k>0) && (pattern[k] != S[i]))
			k = pf[k - 1];

		if (pattern[k] == S[i])
			k++;

		if (k == pattern.length())
			return (i - pattern.length() + 1);//либо продолжаем поиск следующих вхождений
	}

	return (string::npos);
}

void ReplaceSubString(string &inputLine, const string &searchString, const string &replaceString)
{
	if (searchString == replaceString)
		return;

	size_t foundPosition = KMP_Search(inputLine, 0, searchString);
	if (foundPosition == inputLine.npos)
		return;

	size_t currentPosition = 0;
	string result;
	result.reserve(inputLine.length());

	while (foundPosition != inputLine.npos)
	{
		result.append(inputLine, currentPosition, foundPosition - currentPosition);
		result += replaceString;
		currentPosition = foundPosition + searchString.length();
		foundPosition = KMP_Search(inputLine, currentPosition, searchString);
	}

	inputLine = result.append(inputLine, currentPosition, inputLine.length() - currentPosition);
}