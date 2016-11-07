#include "stdafx.h"
#include "DictionaryFunctions.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>

int main()
{
	setlocale(LC_ALL, "Russian");
	std::fstream fs;
	Dictionary dictionary;
	fs.open("словарь", std::ios::out | std::ios::binary);
	SaveDictionaryToFile(fs, dictionary);
	fs.open("словарь", std::ios::in | std::ios::binary);
	GetDictionaryFromFile(fs, dictionary);
	for (auto const& current : dictionary)
		std::cout << current.first << " : " << current.second << '\n';
    return 0;
}

