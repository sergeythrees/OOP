#include "stdafx.h"
#include "DictionaryFunctions.h"
#include <locale>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
int main()
{
	setlocale(LC_ALL, "Russian");
	std::fstream fs;
	Dictionary dictionary;
	Dictionary dict { { "", "" } ,{ "fgdgdfg", "�������" }, { "�����", "�����" } , { "sdsd", "sds" } };
	fs.open("�������", std::ios::out | std::ios::binary);
	SaveDictionaryToFile(fs, dict);
	fs.open("�������", std::ios::in | std::ios::binary);
	GetDictionaryFromFile(fs, dictionary);
	for (auto const& current : dictionary)
		std::cout << current.first << " : " << current.second << '\n';
    return 0;
}

