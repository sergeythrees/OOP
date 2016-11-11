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
	string translation, newWord;
	cout << "¬ведите cлово или пустую строку дл€ отмены" << endl;

	cout << "слово: " << word;
	if (word.empty())
	{
		if (getline(cin, newWord) && newWord.empty())
		{
			cout << endl;
			return false;
		}
	}
	else
		newWord = word;

	cout << endl << "перевод: ";
	if (getline(cin, translation) && !translation.empty())
	{
		InsertNewPair(newWord, translation, dictionary);
		cout << endl;
		return true;
	}

	cout << endl;
	return false;
}

bool GetDictionaryFromFile(const string &fileName, Dictionary &dictionary)
{
	ifstream file(fileName);
	if (file.is_open())
	{
		FillDictionaryFromInputStream(file, dictionary);
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
		PrintDictionaryToOutputStream(fileOut, dictionary);
		fileOut.close();
		return true;
	}
	return false;
}
