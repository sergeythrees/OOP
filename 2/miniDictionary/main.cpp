#include "stdafx.h"
#include <locale>
#include <iostream>
#include <string>
#include "Windows.h"
#include "MainFunctions.h"
#include "ProcessErrors.h"
#include "DictionaryFunctions.h"

using namespace std;

bool wasChangedDictionary = false;

void MainLoop(Dictionary &dictionary);


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (!IsValidArgumentsCount(argc))
		return EXIT_FAILURE;

	Dictionary dictionary;

	if (!GetDictionaryFromFile(argv[1], dictionary))
		cout << "Не удалось считать словарь с файла, будет создан новый файл" << endl;

	MainLoop(dictionary);

	if (wasChangedDictionary && HasUserAgreed("Словарь был изменен, сохранить изменения в файл?"))
		if (!SaveDictionaryToFile(argv[1], dictionary))
			return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void MainLoop(Dictionary &dictionary)
{
	string word;
	cout << "Введите слово для перевода, \":\" для ввода нового(варианта) перевода" 
		 << endl << "или \"...\" для завершения работы со словарем" << endl;
	if (dictionary.empty())
		cout << endl << "Словарь пуст" << endl;
	
	cout << ">";
	while (getline(cin, word) && (word != "..."))
	{
		if (word.empty())
		{
			cout << "Пустая строка, введите слово" << endl;
		}
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
	}
}
