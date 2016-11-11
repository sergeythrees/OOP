#pragma once
#include "stdafx.h"

typedef std::multimap <std::string, std::string> Dictionary;
void GetDictionaryFromFile(std::fstream &fs, Dictionary &sset2);
void SaveDictionaryToFile(std::fstream &fs, Dictionary &temp);
std::string ToLower(const std::string &line);
bool IsWordRussian(const std::string &word);
std::vector<std::string> GetAllTranslations(const std::string &word, Dictionary &dictionary);
void InsertNewPair(const std::string &word, const std::string &translation, Dictionary &dictionary);