#include "stdafx.h"
#include "DictionaryFunctions.h"

void FillDictionaryFromInputStream(istream &input, Dictionary &dictionary)
{
	string word, translation;
	while (getline(input, word) && getline(input, translation))
	{
		dictionary.insert(make_pair(word, translation));
	}
}

void PrintDictionaryToOutputStream(ostream &output, Dictionary &dictionary)
{
	for (auto currentPair : dictionary)
	{
		output << currentPair.first << endl << currentPair.second << endl;
	}
}

vector<string> GetAllTranslations(const string &word, Dictionary &dictionary)
{
	vector<string> translations;

	if (IsWordRussian(word))
	{
		for (auto tCurrent : dictionary)
		{
			if (ToLower(word) == tCurrent.second)
			{
				translations.push_back(tCurrent.first);
			}
		}
	}
	else
	{
		auto translationsRange = dictionary.equal_range(ToLower(word));
		auto tBegin = translationsRange.first;
		auto tEnd = translationsRange.second;
		for (auto tCurrent = tBegin; tCurrent != tEnd; ++tCurrent)
		{
			translations.push_back(tCurrent->second);
		}
	}

	return translations;
}

void InsertNewPair(const string &word, const string &translation, Dictionary &dictionary) //if return true --> dictionary was changed
{
	if (IsWordRussian(word))
		dictionary.insert(make_pair(translation, word));
	else
		dictionary.insert(make_pair(word, translation));
}

bool IsWordRussian(const string &word)
{
	for (auto symbol : word)
	{
		if (!(symbol >= 'À' && symbol <= 'ÿ'))
			return false;
	}
	return true;
}

string ToLower(const string &line)
{
	string result;
	for (auto symbol : line)
	{
		if (symbol >= 'À' && symbol <= 'ß')
			result += symbol + 32;
		else
			result += tolower(symbol);
	}
	return result;
}