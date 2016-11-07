#include "stdafx.h"
#include "../htmlDecode/decode.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)

BOOST_AUTO_TEST_CASE(doesnt_spoil_string)
{
	vector<pair<string, string>> htmlMap = { { "&quot;", "\"" }, { "&apos;", "'" }, { "&lt;", "<" }, { "&gt;", ">" }, { "&amp;", "&" } };
	const string expectedResult = "The quick brown fox jumps over the lazy dog";
	string input = "The quick brown fox jumps over the lazy dog";
	auto result = DecodeHtmlText(input);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_CASE(replace_required_substrings_once)
{
	vector<pair<string, string>> htmlMap = { { "&quot;", "\"" },{ "&apos;", "'" },{ "&lt;", "<" },{ "&gt;", ">" },{ "&amp;", "&" } };
	const string expectedResult = "Cat <says> \"Meow. M&M's";
	string input = "Cat &lt;says&gt; &quot;Meow. M&amp;M&apos;s";
	auto result = DecodeHtmlText(input);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_CASE(replace_required_repeated_substrings)
{
	vector<pair<string, string>> htmlMap = { { "&quot;", "\"" },{ "&apos;", "'" },{ "&lt;", "<" },{ "&gt;", ">" },{ "&amp;", "&" } };

	const string expectedResult = "Cat <says> \"Meow\". M&M's\\\ Cat <says> \"Meow\".";
	string input = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s\\\ Cat &lt;says&gt; &quot;Meow&quot;.";
	auto result = DecodeHtmlText(input);

	BOOST_CHECK(result == expectedResult);
}

BOOST_AUTO_TEST_SUITE_END()
