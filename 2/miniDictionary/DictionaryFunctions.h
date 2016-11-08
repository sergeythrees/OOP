#pragma once
#include "stdafx.h"
#include <map>

typedef std::multimap <std::wstring, std::wstring> Dictionary;
void GetDictionaryFromFile(std::fstream &fs, Dictionary &sset2);
void SaveDictionaryToFile(std::fstream &fs, Dictionary &temp);