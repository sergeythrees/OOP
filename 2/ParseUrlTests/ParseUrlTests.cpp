#include "stdafx.h"
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/variant.hpp>
#include "../ParseUrl/HttpUrl.h"

using namespace std;
using namespace boost;

template <typename Ex, typename Fn>
void VerifyException(Fn && fn, const string & expectedDescription)
{
	BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
		BOOST_CHECK_EQUAL(e.what(), expectedDescription);
		return e.what() == expectedDescription;
	});
}

void VerifyUrl(
	const CHttpUrl& result,
	const string& expectedDomain,
	const string& expectedDocument,
	const Protocol& expectedProtocol,
	const unsigned short expectedPort)
{
	BOOST_CHECK(result.GetProtocol() == expectedProtocol);
	BOOST_CHECK_EQUAL(result.GetDomain(), expectedDomain);
	BOOST_CHECK_EQUAL(result.GetPort(), expectedPort);
	BOOST_CHECK_EQUAL(result.GetDocument(), expectedDocument);
}

BOOST_AUTO_TEST_SUITE(HttpUrl_class)

	BOOST_AUTO_TEST_SUITE(constructor_from_string)
		string urlLine;
		BOOST_AUTO_TEST_CASE(can_be_constructed_from_correct_url_string)
		{
			urlLine =
				"http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title";
			BOOST_CHECK_NO_THROW(CHttpUrl(urlLine.c_str()));
			VerifyUrl(CHttpUrl(urlLine),
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 100);
		}
		BOOST_AUTO_TEST_CASE(can_be_constructed_from_url_line_without_port_value)
		{
			urlLine =
				"http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
			BOOST_CHECK_NO_THROW(CHttpUrl(urlLine.c_str()));
			VerifyUrl(CHttpUrl(urlLine),
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 80);
		}
		BOOST_AUTO_TEST_CASE(can_be_constructed_when_domain_have_not_close_slash)
		{
			urlLine =
				"http://www.mysite.com:90";
			BOOST_CHECK_NO_THROW(CHttpUrl(urlLine.c_str()));
			VerifyUrl(CHttpUrl(urlLine),
				"www.mysite.com", "", Protocol::HTTP, 90);

			urlLine =
				"http://www.mysite.com";
			BOOST_CHECK_NO_THROW(CHttpUrl(urlLine.c_str()));
			VerifyUrl(CHttpUrl(urlLine),
				"www.mysite.com", "", Protocol::HTTP, 80);
		}
		BOOST_AUTO_TEST_CASE(can_be_constructed_when_domain_have_not_dot)
		{
			urlLine =
				"http://www.mysite:90";
			BOOST_CHECK_NO_THROW(CHttpUrl(urlLine.c_str()));
			VerifyUrl(CHttpUrl(urlLine),
				"www.mysite", "", Protocol::HTTP, 90);

			urlLine =
				"http://mysite";
			BOOST_CHECK_NO_THROW(CHttpUrl(urlLine.c_str()));
			VerifyUrl(CHttpUrl(urlLine),
				"mysite", "", Protocol::HTTP, 80);
		}
		BOOST_AUTO_TEST_CASE(can_be_constructed_from_url_line_with_other_protocols)
		{
			urlLine =
				"https://www.mysite.com/docs/document1.html?page=30&lang=en#title";
			BOOST_CHECK_NO_THROW(CHttpUrl(urlLine.c_str()));
			VerifyUrl(CHttpUrl(urlLine),
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTPS, 443);

			urlLine =
				"ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title";
			BOOST_CHECK_NO_THROW(CHttpUrl(urlLine.c_str()));
			VerifyUrl(CHttpUrl(urlLine),
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::FTP, 21);
		}
		BOOST_AUTO_TEST_CASE(is_case_insensitive)
		{
			BOOST_CHECK_NO_THROW(CHttpUrl url(
				"hTTp://www.mysite.cOm:80/docs/document1.html?page=30&lang=en#title"));
		}
		BOOST_AUTO_TEST_SUITE(should_throw_approppriate_exceptions)
			BOOST_AUTO_TEST_CASE(when_can_not_parse_URL_line)
			{
				VerifyException<invalid_argument>([]() {
					CHttpUrl(""); },
					"Invalid URL line");
				VerifyException<invalid_argument>([]() {
					CHttpUrl("http:/ur"); },
					"Invalid URL line");
				VerifyException<invalid_argument>([]() {
					CHttpUrl("http:///"); },
					"Invalid URL line");
			}
			BOOST_AUTO_TEST_CASE(when_port_value_is_out_of_integer_range)
			{
				VerifyException<invalid_argument>([]() {
					CHttpUrl("http://ur.ru:2222222222/"); },
					"Port value is out of integer range");
			}
			BOOST_AUTO_TEST_CASE(when_port_value_is_out_of_port_allow_range)
			{
				VerifyException<invalid_argument>([]() {
					CHttpUrl("http://ur.ru:-1/"); },
					"Port value is out of port allow range (1..65535)");
				VerifyException<invalid_argument>([]() {
					CHttpUrl("http://ur.ru:0/"); },
					"Port value is out of port allow range (1..65535)");
				VerifyException<invalid_argument>([]() {
					CHttpUrl("http://ur.ru:65536/"); },
					"Port value is out of port allow range (1..65535)");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(can_get_itself_data)
		{
			CHttpUrl url("http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title");
			BOOST_CHECK_EQUAL(url.GetDomain(), "www.mysite.com");
			BOOST_CHECK_EQUAL(url.GetDocument(), "/docs/document1.html?page=30&lang=en#title");
			BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
			BOOST_CHECK_EQUAL(url.GetPort(), 100);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()