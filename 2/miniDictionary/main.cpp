#include "stdafx.h"
#include "Windows.h"
#include <iostream>
#include <iterator>
#include <locale>
#include <fstream>
#include <string>
#include <map>
#include "MainFunctions.h"
#include "DictionaryFunctions.h"

using namespace std;

static const string EXIT_STRING = "...";
bool wasChangedDictionary = false;

void MainLoop(Dictionary dictionary);


int main()
{
	setlocale(LC_ALL, "Russian");

	//std::fstream file;
	//Dictionary dictionary;
	//Dictionary dict{ { "", "" } ,{ "fgdgdfg", "ывываыа" },{ "ывава", "ваыва" } ,{ "sdsd", "sds" } };
	//file.open("словарь", std::ios::out | std::ios::binary);
	//SaveDictionaryToFile(file, dict);

	//file.open("словарь", std::ios::in | std::ios::binary);
	//GetDictionaryFromFile(file, dictionary);

	multimap<string, string> dictionary =
	{
		{ "apple" , "€блоко" },{ "black" , "темный" },{ "dark" , "темный" } ,
		{ "key" , "ключ" },{ "key" , "клавиша" },{ "orange" , "апельсин" },
		{ "shadow" , "темный" }
	};

	MainLoop(dictionary);

	//if (wasChangedDictionary
	//	&& HasUserAgreed("—ловарь был изменен, сохранить изменени€ в файл?"))
	//{
	//	SaveDictionaryToFile(file, dictionary);
	//}

    return 0;
}

void MainLoop(Dictionary dictionary)
{
	string word;
	cout << "¬ведите слово дл€ перевода или \"" + EXIT_STRING + "\" дл€ завершени€ работы со словарем" << endl;
	cout << ">";

	while (getline(cin, word) && (word != EXIT_STRING))
	{
		if (word.empty())
			cout << "ѕуста€ строка, введите слово" << endl;
		else
		{
			auto foundTranslations = GetAllTranslations(word, dictionary);

			if (!foundTranslations.empty())
				PrintFormatedTranlations(foundTranslations, cout);
			else
			{
				if (HasUserAgreed("ѕеревод не найден. ¬нести новое слово в словарь?"))
				{
					CreateNewPair(word, dictionary);
					wasChangedDictionary = true;
				}
			}

		}
		cout << ">";
		//cin.clear();
	}
}
