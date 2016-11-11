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

	GetDictionaryFromFile("�������.txt", dictionary);

	MainLoop(dictionary);

	if (wasChangedDictionary
		&& HasUserAgreed("������� ��� �������, ��������� ��������� � ����?"))
	{
		if (!SaveDictionaryToFile("�������.txt", dictionary))
		{
			cout << "�� ������� ��������� ������� � ����" << endl;
		}
	}

    return 0;
}

void MainLoop(Dictionary &dictionary)
{
	string word;
	cout << "������� ����� ��� ��������, \":\" ��� ����� ������(��������) �������� ��� \"...\" ��� ���������� ������ �� ��������" << endl;
	cout << ">";

	while (getline(cin, word) && (word != "..."))
	{
		if (word.empty())
			cout << "������ ������, ������� �����" << endl;
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
		//cin.clear();
	}
}
