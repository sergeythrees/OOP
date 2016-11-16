#include "stdafx.h"
#include "../miniDictionary/DictionaryFunctions.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(ToLower_function)

BOOST_AUTO_TEST_CASE(should_replace_russian_and_english_letters_in_word_to_lower)
{
	BOOST_CHECK(ToLower("APPLE") == "apple"); 
	BOOST_CHECK(ToLower("Apple") == "apple");
	BOOST_CHECK(ToLower("ßÁËÎÊÎ") == "ÿáëîêî");
	BOOST_CHECK(ToLower("ßáëîêî") == "ÿáëîêî");
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(IsRussianWord_function)

BOOST_AUTO_TEST_CASE(should_return_false_if_word_contain_not_russian_charaster)
{
	BOOST_CHECK(IsWordRussian("apple") == false);
	BOOST_CHECK(IsWordRussian("ßáëîêîApple") == false);
	BOOST_CHECK(IsWordRussian("ßáëîêî") == true);
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(GetAllTranslation_function)

BOOST_AUTO_TEST_CASE(should_return_all_translations_of_russian_word_to_english)
{
	Dictionary dictionary =
	{ 
		{ "apple" , "ÿáëîêî" }, { "black" , "òåìíûé" }, { "dark" , "òåìíûé" } ,	
		{ "key" , "êëþ÷" }, { "key" , "êëàâèøà" }, {"orange" , "àïåëüñèí" }, 
		{ "shadow" , "òåìíûé" } 
	};

	vector<string> translations = { "black" , "dark" , "shadow"};
	BOOST_CHECK(GetAllTranslations("òåìíûé", dictionary) == translations);
	BOOST_CHECK(GetAllTranslations("Òåìíûé", dictionary) == translations);
}

BOOST_AUTO_TEST_CASE(should_return_all_translations_of_english_word_to_russian)
{
	Dictionary dictionary =
	{
		{ "apple" , "ÿáëîêî" },{ "black" , "òåìíûé" },{ "dark" , "òåìíûé" } ,
		{ "key" , "êëþ÷" },{ "key" , "êëàâèøà" },{ "orange" , "àïåëüñèí" },
		{ "shadow" , "òåìíûé" }
	};

	vector<string> translations = { "êëþ÷" , "êëàâèøà"};
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
	{ { "key" , "êëàâèøà" } };
	Dictionary UpdatedDictionary =
	{ { "key" , "êëàâèøà" }, { "key" , "êëþ÷" }};

	InsertNewPair("key", "êëàâèøà", EmptyDictionary);
	BOOST_CHECK(EmptyDictionary == dictionary);

	InsertNewPair("key", "êëþ÷", dictionary);
	BOOST_CHECK(dictionary == UpdatedDictionary);
}

BOOST_AUTO_TEST_CASE(should_insert_new_translation_from_russian_to_english_into_dictionary)
{
	Dictionary EmptyDictionary;
	Dictionary dictionary =
	{ { "key" , "êëàâèøà" } };
	Dictionary UpdatedDictionary =
	{ { "key" , "êëàâèøà" },{ "key" , "êëþ÷" }};

	InsertNewPair("êëàâèøà", "key", EmptyDictionary);
	BOOST_CHECK(EmptyDictionary == dictionary);

	InsertNewPair("êëþ÷", "key", dictionary);
	BOOST_CHECK(dictionary == UpdatedDictionary);
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(FillDictionaryFromInputStream_function)

BOOST_AUTO_TEST_CASE(should_makes_empty_dictionary_from_empty_file)
{
	stringstream input;
	Dictionary EmptyDictionary;

	FillDictionaryFromInputStream(input, EmptyDictionary);
	BOOST_CHECK(EmptyDictionary.empty());
}

BOOST_AUTO_TEST_CASE(should_add_new_pair_to_non_empty_dictionary)
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
