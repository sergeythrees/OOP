#include "stdafx.h"
#include "../miniDictionary/DictionaryFunctions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ToLower_function)

BOOST_AUTO_TEST_CASE(should_replace_to_lower_russian_letters)
{
	BOOST_CHECK(ToLower("ЯБЛОКО") == "яблоко");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IsRussianWord_function)

BOOST_AUTO_TEST_CASE(should_return_false_if_word_contain_not_russian_charaster)
{
	BOOST_CHECK(IsWordRussian("apple") == false);
	BOOST_CHECK(IsWordRussian("APPLE") == false);
	BOOST_CHECK(IsWordRussian("ЯблокоApple") == false);
	BOOST_CHECK(IsWordRussian("Яблоко") == true);
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


