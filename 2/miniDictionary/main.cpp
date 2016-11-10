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
	if (ToLower("������") == "������")
		cout << "dfsdf";

	std::fstream file;
	Dictionary dictionary;
	Dictionary dict{ { "", "" } ,{ "fgdgdfg", "�������" },{ "�����", "�����" } ,{ "sdsd", "sds" } };
	file.open("�������", std::ios::out | std::ios::binary);
	SaveDictionaryToFile(file, dict);

	file.open("�������", std::ios::in | std::ios::binary);
	GetDictionaryFromFile(file, dictionary);

	WorkWithDictionary(dictionary);

	if (wasChangedDictionary
		&& HasUserAgreed("������� ��� �������, ��������� ��������� � ����? (Y/N)"))
	{
		SaveDictionaryToFile(file, dictionary);
	}

    return 0;
}

void WorkWithDictionary(Dictionary dictionary)
{
	string word;
	cout << "������� ����� ��� �������� ��� \"" + EXIT_STRING + "\" ��� ���������� ������ �� ��������" << endl;
	cout << ">";
	while (getline(cin, word) && (word != EXIT_STRING))
	{
		if (word.empty())
		{
			cout << "������ ������, ������� �����" << endl;
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
				cout << "������� �� ������" << endl;
				if (HasUserAgreed("������ ����� ����� � �������? (Y/N)"))
				{
					CreateNewPair(word, dictionary);
					wasChangedDictionary = true;
				}
			}

		}
		cout << ">";
	}
}

