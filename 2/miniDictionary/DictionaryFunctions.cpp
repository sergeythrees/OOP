#include "stdafx.h"
#include "DictionaryFunctions.h"

using namespace std;

namespace
{
	static const map<char, char> toLowerRussianLettersMap({ 
		{ 'À', 'à' },{ 'Á', 'á' },{ 'Â', 'â' },{ 'Ã', 'ã' },{ 'Ä', 'ä' },
		{ 'Å', 'å' },{ '¨', '¸' },{ 'Æ', 'æ' },{ 'Ç', 'ç' },{ 'È', 'è' },
		{ 'É', 'é' },{ 'Ê', 'ê' },{ 'Ë', 'ë' },{ 'Ì', 'ì' },{ 'Í', 'í' },
		{ 'Î', 'î' },{ 'Ï', 'ï' },{ 'Ð', 'ð' },{ 'Ñ', 'ñ' },{ 'Ò', 'ò' },
		{ 'Ó', 'ó' },{ 'Ô', 'ô' },{ 'Õ', 'õ' },{ 'Ö', 'ö' },{ '×', '÷' },
		{ 'Ø', 'ø' },{ 'Ù', 'ù' },{ 'Ú', 'ú' },{ 'Û', 'û' },{ 'Ü', 'ü' },
		{ 'Ý', 'ý' },{ 'Þ', 'þ' },{ 'ß', 'ÿ' }
	});
}

void FillDictionaryFromInputStream(istream &input, Dictionary &dictionary)
{
	string word, translation;
	while (getline(input, word) && getline(input, translation))
	{
		dictionary.emplace(word, translation);
	}
}

void PrintDictionaryToOutputStream(ostream &output, const Dictionary &dictionary)
{
	for (auto currentPair : dictionary)
	{
		output << currentPair.first << endl << currentPair.second << endl;
	}
}

vector<string> GetAllTranslations(const string &word, const Dictionary &dictionary)
{
	vector<string> translations;
	string lWord = ToLower(word);

	if (IsWordRussian(word))
	{
		for (auto tCurrent : dictionary)
		{
			if (lWord == tCurrent.second)
			{
				translations.push_back(tCurrent.first);
			}
		}
	}
	else
	{
		auto translationsRange = dictionary.equal_range(lWord);
		auto tBegin = translationsRange.first;
		auto tEnd = translationsRange.second;
		for (auto tCurrent = tBegin; tCurrent != tEnd; ++tCurrent)
		{
			translations.push_back(tCurrent->second);
		}
	}

	return translations;
}

bool InsertNewPair(const string &word, const string &translation, Dictionary &dictionary) //if return true --> dictionary was changed
{
	if (IsWordRussian(word) && IsWordEnglish(translation))
		dictionary.emplace(ToLower(translation), ToLower(word));
	else if (IsWordRussian(translation) && IsWordEnglish(word))
		dictionary.emplace(ToLower(word), ToLower(translation));
	else
		return false;
	return true;
}

bool IsWordRussian(const string &word)
{
	for (auto symbol : word)
	{
		if (!(symbol >= 'À' && symbol <= 'ÿ'))
			return false;
	}
	return true;
}

bool IsWordEnglish(const string &word)
{
	for (auto symbol : word)
	{
		if (!(symbol >= 'A' && symbol <= 'z'))
			return false;
	}
	return true;
}

string ToLower(const string &line)
{
	string result;
	for (auto symbol : line)
	{
		if (toLowerRussianLettersMap.count(symbol) > 0)
			result += toLowerRussianLettersMap.at(symbol);
		else
			result += tolower(symbol);
	}
	return result;
}