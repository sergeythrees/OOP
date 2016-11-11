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
	//Dictionary dict{ { "", "" } ,{ "fgdgdfg", "�������" },{ "�����", "�����" } ,{ "sdsd", "sds" } };
	//file.open("�������", std::ios::out | std::ios::binary);
	//SaveDictionaryToFile(file, dict);

	//file.open("�������", std::ios::in | std::ios::binary);
	//GetDictionaryFromFile(file, dictionary);

	multimap<string, string> dictionary =
	{
		{ "apple" , "������" },{ "black" , "������" },{ "dark" , "������" } ,
		{ "key" , "����" },{ "key" , "�������" },{ "orange" , "��������" },
		{ "shadow" , "������" }
	};

	MainLoop(dictionary);

	//if (wasChangedDictionary
	//	&& HasUserAgreed("������� ��� �������, ��������� ��������� � ����?"))
	//{
	//	SaveDictionaryToFile(file, dictionary);
	//}

    return 0;
}

void MainLoop(Dictionary dictionary)
{
	string word;
	cout << "������� ����� ��� �������� ��� \"" + EXIT_STRING + "\" ��� ���������� ������ �� ��������" << endl;
	cout << ">";

	while (getline(cin, word) && (word != EXIT_STRING))
	{
		if (word.empty())
			cout << "������ ������, ������� �����" << endl;
		else
		{
			auto foundTranslations = GetAllTranslations(word, dictionary);

			if (!foundTranslations.empty())
				PrintFormatedTranlations(foundTranslations, cout);
			else
			{
				if (HasUserAgreed("������� �� ������. ������ ����� ����� � �������?"))
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
