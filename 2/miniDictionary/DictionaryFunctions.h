#pragma once
#include "stdafx.h"
#include <map>

typedef std::multimap <std::string, std::string> Dictionary;
void GetDictionaryFromFile(std::fstream &fs, Dictionary &sset2);
void SaveDictionaryToFile(std::fstream &fs, Dictionary &temp);