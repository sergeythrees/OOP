#include "stdafx.h"
#include "../miniDictionary/DictionaryFunctions.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(ToLower_function)

BOOST_AUTO_TEST_CASE(should_replace_russian_and_english_letters_in_word_to_lower)
{
	BOOST_CHECK(ToLower("APPLE") == "apple");
	BOOST_CHECK(ToLower("Apple") == "apple");
	BOOST_CHECK(ToLower("������") == "������");
	BOOST_CHECK(ToLower("������") == "������");
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(IsRussianWord_function)

BOOST_AUTO_TEST_CASE(should_return_false_if_word_contain_not_russian_charaster)
{
	BOOST_CHECK(IsWordRussian("apple") == false);
	BOOST_CHECK(IsWordRussian("������Apple") == false);
	BOOST_CHECK(IsWordRussian("������") == true);
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(GetAllTranslation_function)

BOOST_AUTO_TEST_CASE(should_return_all_translations_of_russian_word_to_english)
{
	multimap<string, string> Dictionary =
	{
		{ "apple" , "������" },{ "black" , "������" },{ "dark" , "������" } ,
		{ "key" , "����" },{ "key" , "�������" },{ "orange" , "��������" },
		{ "shadow" , "������" }
	};

	vector<string> translations = { "black" , "dark" , "shadow" };
	BOOST_CHECK(GetAllTranslations("������", Dictionary) == translations);
	BOOST_CHECK(GetAllTranslations("������", Dictionary) == translations);
}

BOOST_AUTO_TEST_CASE(should_return_all_translations_of_english_word_to_russian)
{
	multimap<string, string> Dictionary =
	{
		{ "apple" , "������" },{ "black" , "������" },{ "dark" , "������" } ,
		{ "key" , "����" },{ "key" , "�������" },{ "orange" , "��������" },
		{ "shadow" , "������" }
	};

	vector<string> translations = { "����" , "�������" };
	BOOST_CHECK(GetAllTranslations("key", Dictionary) == translations);
	BOOST_CHECK(GetAllTranslations("Key", Dictionary) == translations);
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(InsertNewPair_function)

BOOST_AUTO_TEST_CASE(should_insert_new_translation_from_english_word_to_russian_into_dictionary)
{
	multimap<string, string> EmptyDictionary;
	multimap<string, string> Dictionary =
	{ { "key" , "�������" } };
	multimap<string, string> UpdatedDictionary =
	{ { "key" , "�������" },{ "key" , "����" }, };

	InsertNewPair("key", "�������", EmptyDictionary);
	BOOST_CHECK(EmptyDictionary == Dictionary);

	InsertNewPair("key", "����", Dictionary);
	BOOST_CHECK(Dictionary == UpdatedDictionary);
}

BOOST_AUTO_TEST_CASE(should_insert_new_translation_from_russian_word_to_english_into_dictionary)
{
	multimap<string, string> EmptyDictionary;
	multimap<string, string> Dictionary =
	{ { "key" , "�������" } };
	multimap<string, string> UpdatedDictionary =
	{ { "key" , "�������" },{ "key" , "����" }, };

	InsertNewPair("�������", "key", EmptyDictionary);
	BOOST_CHECK(EmptyDictionary == Dictionary);

	InsertNewPair("����", "key", Dictionary);
	BOOST_CHECK(Dictionary == UpdatedDictionary);
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(PrintDictionaryToOutputStream_function)

BOOST_AUTO_TEST_CASE(should_makes_empty_file_from_empty_dictionary)
{
	stringstream output;
	Dictionary emptyDictionary;

	PrintDictionaryToOutputStream(output, emptyDictionary);
	BOOST_CHECK(emptyDictionary.empty());
}

BOOST_AUTO_TEST_CASE(should_print_dictionary_to_file)
{
	stringstream output;
	Dictionary dictionary =
	{ { "key", "�������" },{ "key", "����" } };

	PrintDictionaryToOutputStream(output, dictionary);
	BOOST_CHECK(output.str() == "key\n�������\nkey\n����\n");
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(FillDictionaryFromInputStream_function)

BOOST_AUTO_TEST_CASE(should_makes_empty_dictionary_from_empty_file)
{
	stringstream input;
	Dictionary emptyDictionary;

	FillDictionaryFromInputStream(input, emptyDictionary);
	BOOST_CHECK(emptyDictionary.empty());
}

BOOST_AUTO_TEST_CASE(should_fill_dictionary_from_file)
{
	stringstream input;
	Dictionary dictionary;
	Dictionary updatedDictionary =
	{ { "key", "�������" }, { "key", "����" } };

	PrintDictionaryToOutputStream(input, updatedDictionary);
	FillDictionaryFromInputStream(input, dictionary);
	BOOST_CHECK(dictionary == updatedDictionary);
}

BOOST_AUTO_TEST_SUITE_END()