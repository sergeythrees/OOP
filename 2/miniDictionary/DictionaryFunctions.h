#pragma once

typedef std::multimap <std::string, std::string> Dictionary;
void FillDictionaryFromInputStream(std::istream &input, Dictionary &dictionary);
void PrintDictionaryToOutputStream(std::ostream &output, const Dictionary &dictionary);
std::string ToLower(const std::string &line);
bool IsWordRussian(const std::string &word);
bool IsWordEnglish(const std::string &word);
std::vector<std::string> GetAllTranslations(const std::string &word, const Dictionary &dictionary);
bool InsertNewPair(const std::string &word, const std::string &translation, Dictionary &dictionary);