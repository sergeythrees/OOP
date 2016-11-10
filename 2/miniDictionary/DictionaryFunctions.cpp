#include "stdafx.h"
#include "DictionaryFunctions.h"
#include <fstream>
#include <iostream>
//#include <boost/serialization/map.hpp>
//#include <boost/serialization/string.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
#include <algorithm>

using namespace std;

void GetDictionaryFromFile(fstream &file, Dictionary &dictionary)
{
	/*if (file.is_open())
	{
	boost::archive::binary_iarchive bia(file);
	bia >> dictionary;
	file.close();
	}*/
}

void SaveDictionaryToFile(fstream &file, Dictionary &dictionary)
{
	//if (file.is_open())
	//{
	//	boost::archive::binary_oarchive boa(file);
	//	boa << dictionary;
	//	file.close();
	//}
}

string FindTranslations(const string word, Dictionary &dictionary)
{
	string translations;
	for (auto currentPair : dictionary)
	{
		if (word == currentPair.first)
		{
			translations.append(currentPair.second + " | ");
		}
		if (word == currentPair.second)
		{
			translations.append(currentPair.first + " | ");
		}
	}
	return translations;
}

void CreateNewPair(string word, Dictionary &dictionary) //if return true --> dictionary was changed
{


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