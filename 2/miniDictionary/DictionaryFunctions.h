#pragma once
#include "stdafx.h"

typedef std::multimap <std::string, std::string> Dictionary;
void GetDictionaryFromFile(std::fstream &fs, Dictionary &sset2);
void SaveDictionaryToFile(std::fstream &fs, Dictionary &temp);
std::string ToLower(const std::string &line);