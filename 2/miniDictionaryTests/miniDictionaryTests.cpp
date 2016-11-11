#include "stdafx.h"
#include "../miniDictionary/DictionaryFunctions.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(ToLower_function)

BOOST_AUTO_TEST_CASE(should_replace_to_lower_russian_letters)
{
	BOOST_CHECK(ToLower("������") == "������");
}

BOOST_AUTO_TEST_SUITE_END()


/////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(IsRussianWord_function)

BOOST_AUTO_TEST_CASE(should_return_false_if_word_contain_not_russian_charaster)
{
	BOOST_CHECK(IsWordRussian("apple") == false);
	BOOST_CHECK(IsWordRussian("APPLE") == false);
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

BOOST_AUTO_TEST_CASE(should_insert_new_pair_from_english_and_russian_words_into_dictionary)
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

BOOST_AUTO_TEST_SUITE_END()

//BOOST_AUTO_TEST_CASE(replace_required_substrings_once)
//{
//	vector<pair<string, string>> htmlMap = { { "&quot;", "\"" },{ "&apos;", "'" },{ "&lt;", "<" },{ "&gt;", ">" },{ "&amp;", "&" } };
//	const string expectedResult = "Cat <says> \"Meow. M&M's";
//	string input = "Cat &lt;says&gt; &quot;Meow. M&amp;M&apos;s";
//	auto result = DecodeHtmlText(input);
//
//	BOOST_CHECK(result == expectedResult);
//}
//
//BOOST_AUTO_TEST_CASE(replace_required_repeated_substrings)
//{
//	vector<pair<string, string>> htmlMap = { { "&quot;", "\"" },{ "&apos;", "'" },{ "&lt;", "<" },{ "&gt;", ">" },{ "&amp;", "&" } };
//
//	const string expectedResult = "Cat <says> \"Meow\". M&M's\\\ Cat <says> \"Meow\".";
//	string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s\\\ Cat &lt;says&gt; &quot;Meow&quot;.";
//	auto result = DecodeHtmlText(input);
//
//	BOOST_CHECK(result == expectedResult);
//}


