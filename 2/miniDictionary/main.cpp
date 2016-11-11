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
		cout << "�� ������� ������� ������� � �����, ����� ������ ����� ����" << endl;

	MainLoop(dictionary);

	if (wasChangedDictionary && HasUserAgreed("������� ��� �������, ��������� ��������� � ����?"))
		if (!SaveDictionaryToFile(argv[1], dictionary))
			return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void MainLoop(Dictionary &dictionary)
{
	string word;
	cout << "������� ����� ��� ��������, \":\" ��� ����� ������(��������) ��������" 
		 << endl << "��� \"...\" ��� ���������� ������ �� ��������" << endl;
	if (dictionary.empty())
		cout << endl << "������� ����" << endl;
	
	cout << ">";
	while (getline(cin, word) && (word != "..."))
	{
		if (word.empty())
		{
			cout << "������ ������, ������� �����" << endl;
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
				cout << "������� �� ������." << endl;
				if (HasInsertedNewPairInToDictionary(word, dictionary))
						wasChangedDictionary = true;
			}
		}
		cout << ">";
	}
}
