#pragma once
#include "stdafx.h"
#include "DictionaryFunctions.h"

bool HasUserAgreed(std::string question);
void PrintFormatedTranlations(const std::vector<std::string> &translations, std::ostream &output);