#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef multimap <string, string> Dictionary;
void FillDictionaryFromInputStream(istream &input, Dictionary &dictionary);
void PrintDictionaryToOutputStream(ostream &output, Dictionary &dictionary);
string ToLower(const string &line);
bool IsWordRussian(const string &word);
bool IsWordEnglish(const string &word);
vector<string> GetAllTranslations(const string &word, Dictionary &dictionary);
bool InsertNewPair(const string &word, const string &translation, Dictionary &dictionary);