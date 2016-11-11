#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "MainFunctions.h"
#include "DictionaryFunctions.h"

using namespace std;

bool HasUserAgreed(string question)
{
	cout << question << " (намжмите \"Y\", если да)" << endl;

	string answer;

	cin >> answer;
	if (answer == "Y" || answer == "y")
	{
		return true;
	}

	return false;
}

void PrintFormatedTranlations(const vector<string> &translations, ostream &output)
{
	for (auto tCurrent : translations)
	{
		output << "   - " << tCurrent << "\n";
	}
}

bool HasInsertedNewPairInToDictionary(const string &word, Dictionary &dictionary)
{
	string translation;
	cout << "¬ведите перевод или пустую строку дл€ отмены" << endl;
	if (getline(cin, translation) && translation.empty())
	{
		InsertNewPair(word, translation, dictionary);
		return true;
	}

	return false;
}
