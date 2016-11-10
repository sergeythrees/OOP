#include "stdafx.h"
#include "MainFunctions.h"
#include "DictionaryFunctions.h"
#include <locale>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

bool wasChangedDictionary = false;

static const string EXIT_STRING = "...";

void WorkWithDictionary(Dictionary dictionary);

int main()
{
	setlocale(LC_ALL, "Russian");
	if (ToLower("яЅЋќ ќ") == "€блоко")
		cout << "dfsdf";

	std::fstream file;
	Dictionary dictionary;
	Dictionary dict{ { "", "" } ,{ "fgdgdfg", "ывываыа" },{ "ывава", "ваыва" } ,{ "sdsd", "sds" } };
	file.open("словарь", std::ios::out | std::ios::binary);
	SaveDictionaryToFile(file, dict);

	file.open("словарь", std::ios::in | std::ios::binary);
	GetDictionaryFromFile(file, dictionary);

	WorkWithDictionary(dictionary);

	if (wasChangedDictionary
		&& HasUserAgreed("—ловарь был изменен, сохранить изменени€ в файл? (Y/N)"))
	{
		SaveDictionaryToFile(file, dictionary);
	}

    return 0;
}

void WorkWithDictionary(Dictionary dictionary)
{
	string word;
	cout << "¬ведите слово дл€ перевода или \"" + EXIT_STRING + "\" дл€ завершени€ работы со словарем" << endl;
	cout << ">";
	while (getline(cin, word) && (word != EXIT_STRING))
	{
		if (word.empty())
		{
			cout << "ѕуста€ строка, введите слово" << endl;
		}
		else
		{
			string foundTranslations = FindTranslations(word, dictionary);

			if (!foundTranslations.empty())
			{
				cout << word << " : " << foundTranslations << endl;
			}
			else
			{
				cout << "ѕеревод не найден" << endl;
				if (HasUserAgreed("¬нести новое слово в словарь? (Y/N)"))
				{
					CreateNewPair(word, dictionary);
					wasChangedDictionary = true;
				}
			}

		}
		cout << ">";
	}
}

