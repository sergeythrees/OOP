#include "stdafx.h"
#include "../miniDictionary/DictionaryFunctions.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(ToLower_function)

BOOST_AUTO_TEST_CASE(should_replace_russian_and_english_letters_in_word_to_lower)
{
	BOOST_CHECK(ToLower("APPLE") == "apple"); 
	BOOST_CHECK(ToLower("Apple") == "apple");
	BOOST_CHECK(ToLower("ЯБЛОКО") == "яблоко");
	BOOST_CHECK(ToLower("Яблоко") == "яблоко");
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(IsRussianWord_function)

BOOST_AUTO_TEST_CASE(should_return_false_if_word_contain_not_russian_charaster)
{
	BOOST_CHECK(IsWordRussian("apple") == false);
	BOOST_CHECK(IsWordRussian("ЯблокоApple") == false);
	BOOST_CHECK(IsWordRussian("Яблоко") == true);
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(GetAllTranslation_function)

BOOST_AUTO_TEST_CASE(should_return_all_translations_of_russian_word_to_english)
{
	Dictionary dictionary =
	{ 
		{ "apple" , "яблоко" }, { "black" , "темный" }, { "dark" , "темный" } ,	
		{ "key" , "ключ" }, { "key" , "клавиша" }, {"orange" , "апельсин" }, 
		{ "shadow" , "темный" } 
	};

	vector<string> translations = { "black" , "dark" , "shadow"};
	BOOST_CHECK(GetAllTranslations("темный", dictionary) == translations);
	BOOST_CHECK(GetAllTranslations("Темный", dictionary) == translations);
}

BOOST_AUTO_TEST_CASE(should_return_all_translations_of_english_word_to_russian)
{
	Dictionary dictionary =
	{
		{ "apple" , "яблоко" },{ "black" , "темный" },{ "dark" , "темный" } ,
		{ "key" , "ключ" },{ "key" , "клавиша" },{ "orange" , "апельсин" },
		{ "shadow" , "темный" }
	};

	vector<string> translations = { "ключ" , "клавиша"};
	BOOST_CHECK(GetAllTranslations("key", dictionary) == translations);
	BOOST_CHECK(GetAllTranslations("Key", dictionary) == translations);
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(InsertNewPair_function)

BOOST_AUTO_TEST_CASE(should_insert_new_translation_from_english_to_russian_into_dictionary)
{
	Dictionary EmptyDictionary;
	Dictionary dictionary =
	{ { "key" , "клавиша" } };
	Dictionary UpdatedDictionary =
	{ { "key" , "клавиша" },{ "key" , "ключ" } };

	InsertNewPair("key", "клавиша", EmptyDictionary);
	BOOST_CHECK(EmptyDictionary == dictionary);

	InsertNewPair("key", "ключ", dictionary);
	BOOST_CHECK(dictionary == UpdatedDictionary);
}

BOOST_AUTO_TEST_CASE(should_insert_new_translation_from_russian_to_english_into_dictionary)
{
	Dictionary EmptyDictionary;
	Dictionary dictionary =
	{ { "key" , "клавиша" } };
	Dictionary UpdatedDictionary =
	{ { "key" , "клавиша" },{ "key" , "ключ" } };

	InsertNewPair("клавиша", "key", EmptyDictionary);
	BOOST_CHECK(EmptyDictionary == dictionary);

	InsertNewPair("ключ", "key", dictionary);
	BOOST_CHECK(dictionary == UpdatedDictionary);
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
	Dictionary dictionary =
	{ { "key", "клавиша" } };
	Dictionary UpdatedDictionary =
	{ { "key", "клавиша" }, { "key", "ключ" } };

	input << "key" << endl << "ключ" << endl;
	FillDictionaryFromInputStream(input, dictionary);
	BOOST_CHECK(dictionary == UpdatedDictionary);
}

BOOST_AUTO_TEST_SUITE_END()
