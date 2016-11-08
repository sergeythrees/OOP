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
	Dictionary dict{ { L"", L"" } ,{ L"fgdgdfg", L"ûגûגאûא" }, { L"ûגאגא", L"גאûגא" } , { L"sdsd", L"sds" } };
	fs.open("סכמגאנü", std::ios::out | std::ios::binary);
	SaveDictionaryToFile(fs, dict);
	fs.open("סכמגאנü", std::ios::in | std::ios::binary);
	GetDictionaryFromFile(fs, dictionary);
	for (auto const& current : dictionary)
		std::wcout << current.first << " : " << current.second << '\n';
    return 0;
}

