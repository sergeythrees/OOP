#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <algorithm>
#include <vector>
#include <set>
#include "DictionaryFunctions.h"

using namespace std;

void FillDictionaryFromSStream(istream &input, Dictionary &dictionary)
{
	string word, translation;
	while (getline(input, word) && getline(input, translation))
	{
		dictionary.insert(make_pair(word, translation));
	}
}

bool GetDictionaryFromFile(const string &fileName, Dictionary &dictionary)
{
	ifstream file(fileName);
	if (file.is_open())
	{
		FillDictionaryFromSStream(file, dictionary);
		file.close();
		return true;
	}
	return false;
}

bool SaveDictionaryToFile(const string &fileName, Dictionary &dictionary)
{
	ofstream fileOut(fileName);
	if (fileOut.is_open())
	{
		for (auto currentPair : dictionary)
		{
			fileOut << currentPair.first << endl << currentPair.second << endl;
		}
		fileOut.close();
		return true;
	}
	return false;
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
		dictionary.insert({ ToLower(translation), ToLower(word) });
	else
		dictionary.insert({ ToLower(word), ToLower(translation) });
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