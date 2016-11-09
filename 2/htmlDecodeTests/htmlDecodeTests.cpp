#include "stdafx.h"
#include "../htmlDecode/decode.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)
	
BOOST_AUTO_TEST_CASE(return_empty_string_from_empty_string)
{
	const string expectedResult = "";
	string input = "";
	auto result = DecodeHtmlText(input);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_CASE(doesnt_change_string_without_html_entities)
{
	const string expectedResult = "The quick brown fox jumps over the lazy dog";
	string input = "The quick brown fox jumps over the lazy dog";
	auto result = DecodeHtmlText(input);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_CASE(replace_required_substrings_once)
{
	const string expectedResult = "Cat <says> \"Meow. M&M's";
	string input = "Cat &lt;says&gt; &quot;Meow. M&amp;M&apos;s";
	auto result = DecodeHtmlText(input);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_CASE(correct_replace_required_repeated_substrings)
{
	const string expectedResult = "Cat &lt<says> \"Meow&qu\"ot;. M&M's\\\ Cat <says> \"Meow\".";
	string input = "Cat &lt&lt;says&gt; &quot;Meow&qu&quot;ot;. M&amp;M&apos;s\\\ Cat &lt;says&gt; &quot;Meow&quot;.";
	auto result = DecodeHtmlText(input);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_SUITE_END()
