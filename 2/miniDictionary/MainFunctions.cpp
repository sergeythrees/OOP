#include "stdafx.h"
#include "MainFunctions.h"
#include "DictionaryFunctions.h"

using namespace std;

bool HasUserAgreed(const string& question)
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
	cout << "Введите cлово или пустую строку для отмены" << endl;

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
		if ((IsWordRussian(newWord) && IsWordEnglish(translation)) || (IsWordRussian(translation) && IsWordEnglish(newWord)))
		{
			if (InsertNewPair(newWord, translation, dictionary))
			{
				cout << endl;
				return true;
			}
		}
		else
		{
			cout << "Новая пара в словаре обязательно должна содержать одно русское " << endl
				<< "и одно английское слово, которые состоят только из букв своего алфавита" << endl;
		}
		

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

	cout << "Не удалось сохранить словарь в файл, попробуйте сменить расположение или имя файла" << endl;
	return false;
}
