#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <locale>
#include <fstream>
#include <string>
#include <map>
#include "Windows.h"
#include "MainFunctions.h"
#include "DictionaryFunctions.h"

using namespace std;

bool wasChangedDictionary = false;

void MainLoop(Dictionary &dictionary);


int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Dictionary dictionary;

	GetDictionaryFromFile("словарь.txt", dictionary);

	MainLoop(dictionary);

	if (wasChangedDictionary
		&& HasUserAgreed("Словарь был изменен, сохранить изменения в файл?"))
	{
		if (!SaveDictionaryToFile("словарь.txt", dictionary))
		{
			cout << "Не удалось сохранить словарь в файл" << endl;
		}
	}

    return 0;
}

void MainLoop(Dictionary &dictionary)
{
	string word;
	cout << "Введите слово для перевода, \":\" для ввода нового(варианта) перевода или \"...\" для завершения работы со словарем" << endl;
	cout << ">";

	while (getline(cin, word) && (word != "..."))
	{
		if (word.empty())
			cout << "Пустая строка, введите слово" << endl;
		else if(word == ":")
		{
			if (HasInsertedNewPairInToDictionary("", dictionary))
				wasChangedDictionary = true;
		}
		else
		{
			auto foundTranslations = GetAllTranslations(word, dictionary);

			if (!foundTranslations.empty())
				PrintFormatedTranlations(foundTranslations, cout);
			else
			{
				cout << "Перевод не найден." << endl;
				if (HasInsertedNewPairInToDictionary(word, dictionary))
						wasChangedDictionary = true;
			}
		}
		cout << ">";
		//cin.clear();
	}
}
