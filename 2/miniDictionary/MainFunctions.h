#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "DictionaryFunctions.h"

using namespace std;

bool HasUserAgreed(string question);
void PrintFormatedTranlations(const vector<string> &translations, ostream &output);
bool HasInsertedNewPairInToDictionary(const string &word, Dictionary &dictionary);
bool GetDictionaryFromFile(const string &fileName, Dictionary &dictionary);
bool SaveDictionaryToFile(const string &fileName, Dictionary &dictionary);