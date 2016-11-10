#pragma once
#include "stdafx.h"

typedef std::multimap <std::string, std::string> Dictionary;
void GetDictionaryFromFile(std::fstream &fs, Dictionary &sset2);
void SaveDictionaryToFile(std::fstream &fs, Dictionary &temp);
std::string ToLower(std::string line);
std::string FindTranslations(const std::string word, Dictionary &dictionary);
void CreateNewPair(std::string word, Dictionary &dictionary);