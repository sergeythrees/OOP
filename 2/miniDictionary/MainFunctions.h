#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "DictionaryFunctions.h"

bool HasUserAgreed(const std::string& question);
void PrintFormatedTranlations(const std::vector<std::string> &translations, std::ostream &output);
bool HasInsertedNewPairInToDictionary(const std::string &word, Dictionary &dictionary);
bool GetDictionaryFromFile(const std::string &fileName, Dictionary &dictionary);
bool SaveDictionaryToFile(const std::string &fileName, Dictionary &dictionary);