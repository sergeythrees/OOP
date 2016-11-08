#include "stdafx.h"
#include "DictionaryFunctions.h"
#include <fstream>
#include <iostream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <locale>

using namespace std;

map<char, char> rusAlphabet 
{
	{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },
	{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },
	{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },
	{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },
	{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },{ '�','�' },
	{'�','�'},{ '�','�' },{ '�','�' } 
};
	

void GetDictionaryFromFile(fstream &file, Dictionary &dictionary)
{
	if (file.is_open())
	{
		boost::archive::binary_iarchive bia(file);
		bia >> dictionary;
		file.close();
	}
}

void SaveDictionaryToFile(fstream &file, Dictionary &dictionary)
{
	if (file.is_open())
	{
		boost::archive::binary_oarchive boa(file);
		boa << dictionary;
		file.close();
	}
}

const string* FindTranslation(const string word, Dictionary &dictionary)
{
	for (Dictionary::iterator currentPair = dictionary.begin(); currentPair != dictionary.end(); ++currentPair)
	{
		if (word == currentPair->first)
		{
			return &(currentPair->second);
		}
		if (word == currentPair->second)
		{
			return &(currentPair->first);
		}
	}

	return nullptr;
}

bool CreateNewPair(string word, Dictionary &dictionary) //if return true --> dictionary was changed
{
	return true;
}

char LetterToLower(const char symbol)
{
	auto foundPair = rusAlphabet.find(symbol);

	if (foundPair->first == symbol)
		return foundPair->second;
	else
		return tolower(symbol);
}

string ToLower(const string line)
{
	string result;
	for (auto symbol : line)
	{
		result += LetterToLower(symbol);
	}
	//boost::transform(line, result.begin(), LetterToLower);
	return result;
}