#include "stdafx.h"
#include "../htmlDecode/decode.h"

using namespace std;

bool VerifyHtmlDecode(string input, string expectedresult)
{
	return expectedresult == DecodeHtmlText(input);
}

BOOST_AUTO_TEST_SUITE(HtmlDecode_function)
	
BOOST_AUTO_TEST_CASE(return_empty_string_from_empty_string)
{
	BOOST_CHECK(VerifyHtmlDecode("", ""));
}

BOOST_AUTO_TEST_CASE(doesnt_change_string_without_html_entities)
{
	BOOST_CHECK(VerifyHtmlDecode("The quick brown fox jumps over the lazy dog", 
				     "The quick brown fox jumps over the lazy dog"));
}

BOOST_AUTO_TEST_CASE(replaces_each_html_entity_with_corresponding_character)
{
	BOOST_CHECK(VerifyHtmlDecode("Cat &lt;says&gt; &quot;Meow. M&amp;M&apos;s", 
				     "Cat <says> \"Meow. M&M's"));
}

BOOST_AUTO_TEST_CASE(correct_replaces_each_html_entity_recursive_character)
{
	BOOST_CHECK(VerifyHtmlDecode(
		"Cat &lt&lt;says&gt; &quot;Meow&qu&quot;ot;. "
		+"M&amp;M&apos;s\\\ Cat &lt;says&gt; &quot;Meow&quot;.", 
		"Cat &lt<says> \"Meow&qu\"ot;. M&M's\\\ Cat <says> \"Meow\"."));
}

BOOST_AUTO_TEST_SUITE_END()
