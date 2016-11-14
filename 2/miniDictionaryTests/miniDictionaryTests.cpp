#include "stdafx.h"
#include <sstream>
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
		{ "apple" , "������" }, { "black" , "������" }, { "dark" , "������" } ,	
		{ "key" , "����" }, { "key" , "�������" }, {"orange" , "��������" }, 
		{ "shadow" , "������" } 
	};

	vector<string> translations = { "black" , "dark" , "shadow"};
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

	vector<string> translations = { "����" , "�������"};
	BOOST_CHECK(GetAllTranslations("key", Dictionary) == translations);
	BOOST_CHECK(GetAllTranslations("Key", Dictionary) == translations);
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(InsertNewPair_function)

BOOST_AUTO_TEST_CASE(should_insert_new_translation_from_english_to_russian_into_dictionary)
{
	multimap<string, string> EmptyDictionary;
	multimap<string, string> Dictionary =
	{ { "key" , "�������" } };
	multimap<string, string> UpdatedDictionary =
	{ { "key" , "�������" }, { "key" , "����" },};

	InsertNewPair("key", "�������", EmptyDictionary);
	BOOST_CHECK(EmptyDictionary == Dictionary);

	InsertNewPair("key", "����", Dictionary);
	BOOST_CHECK(Dictionary == UpdatedDictionary);
}

BOOST_AUTO_TEST_CASE(should_insert_new_translation_from_russian_to_english_into_dictionary)
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


BOOST_AUTO_TEST_SUITE(FillDictionaryFromInputStream_function)

BOOST_AUTO_TEST_CASE(should_correctly_fill_dictionary_from_stringstream)
{
	multimap<string, string> EmptyDictionary;
	multimap<string, string> Dictionary =
	{ { "key" , "�������" } };
	multimap<string, string> UpdatedDictionary =
	{ { "key" , "�������" },{ "key" , "����" }, };

	stringstream input;
	FillDictionaryFromInputStream(input, EmptyDictionary);
	BOOST_CHECK(EmptyDictionary.empty());

	input << "key" << endl << "�������" << endl;
	FillDictionaryFromInputStream(input, EmptyDictionary);
	BOOST_CHECK(EmptyDictionary == Dictionary);

	input << "key" << endl << "����" << endl;
	FillDictionaryFromInputStream(input, EmptyDictionary);
	BOOST_CHECK(EmptyDictionary == UpdatedDictionary);
}



BOOST_AUTO_TEST_SUITE_END()