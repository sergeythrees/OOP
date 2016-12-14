#include "stdafx.h"
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/variant.hpp>
#include "../HttpUrl/HttpUrl.h"
#include "../HttpUrl/CUrlParsingError.h"

using namespace std;
using namespace boost;

template <typename Ex, typename Fn>
void VerifyException(Fn && fn, const string & expectedDescription)
{
	BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
		BOOST_CHECK_EQUAL(e.what() , expectedDescription);
		return e.what() == expectedDescription;
	});
}

void VerifyUrl(const CHttpUrl& result, const string& expectedDomain, const string& expectedDocument, const Protocol& expectedProtocol, const unsigned short expectedPort)
{
	BOOST_CHECK(result.GetProtocol() == expectedProtocol);
	BOOST_CHECK_EQUAL(result.GetDomain(), expectedDomain);
	BOOST_CHECK_EQUAL(result.GetPort(), expectedPort);
	BOOST_CHECK_EQUAL(result.GetDocument(), expectedDocument);
}

BOOST_AUTO_TEST_SUITE(HttpUrl_class)

	BOOST_AUTO_TEST_SUITE(constructor_from_string)
		string urlLine;
		BOOST_AUTO_TEST_CASE(can_be_costructed_from_correct_url_string)
		{
			urlLine = 
				"http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title";
			BOOST_CHECK_NO_THROW(CHttpUrl(urlLine.c_str()));
			VerifyUrl(CHttpUrl(urlLine), 
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 100);
		}
		BOOST_AUTO_TEST_CASE(can_be_costructed_from_url_line_without_port_value)
		{
			urlLine = 
				"http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
			BOOST_CHECK_NO_THROW(CHttpUrl(urlLine.c_str()));
			VerifyUrl(CHttpUrl(urlLine), 
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 80);
		}
		BOOST_AUTO_TEST_CASE(can_be_costructed_when_domain_have_not_close_slash)
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
		BOOST_AUTO_TEST_CASE(can_be_costructed_when_domain_have_not_dot)
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
		BOOST_AUTO_TEST_CASE(can_be_costructed_from_url_line_with_other_protocols)
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

	BOOST_AUTO_TEST_SUITE(constructor_from_parameters)
		BOOST_AUTO_TEST_CASE(can_be_constructed_from_correct_parameters)
		{
			BOOST_CHECK_NO_THROW(CHttpUrl("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 100));
			VerifyUrl(CHttpUrl("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 100),
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 100);
		}
		BOOST_AUTO_TEST_CASE(can_be_constructed_without_port_value)
		{
			BOOST_CHECK_NO_THROW(CHttpUrl("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTP));
			VerifyUrl(CHttpUrl("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTP),
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 80);

			BOOST_CHECK_NO_THROW(CHttpUrl("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTPS));
			VerifyUrl(CHttpUrl("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTPS),
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTPS, 443);

			BOOST_CHECK_NO_THROW(CHttpUrl("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::FTP));
			VerifyUrl(CHttpUrl("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::FTP),
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::FTP, 21);
		}
		BOOST_AUTO_TEST_CASE(can_be_constructed_without_port_and_protocol_value)
		{
			
			BOOST_CHECK_NO_THROW(CHttpUrl("www.mysite.com", "docs/document1.html?page=30&lang=en#title"));
			VerifyUrl(CHttpUrl("www.mysite.com", "docs/document1.html?page=30&lang=en#title"),
				"www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 80);
		}
		BOOST_AUTO_TEST_SUITE(should_throw_approppriate_exceptions)
			BOOST_AUTO_TEST_CASE(when_parameters_are_incorrect)
			{
				VerifyException<invalid_argument>([]() {
					CHttpUrl("", "/index.html"); },
					"Domain must not be empty");
			}
			BOOST_AUTO_TEST_CASE(when_port_value_is_out_of_port_allow_range)
			{
				VerifyException<invalid_argument>([]() {
					CHttpUrl("mysite.com", "/index.html", Protocol::HTTP, 0); },
					"Port value is out of port allow range (1..65535)");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(can_get_itself_data)
		{
			CHttpUrl url("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 100);
			BOOST_CHECK_EQUAL(url.GetDomain(), "www.mysite.com");
			BOOST_CHECK_EQUAL(url.GetDocument(), "/docs/document1.html?page=30&lang=en#title");
			BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
			BOOST_CHECK_EQUAL(url.GetPort(), 100);
			BOOST_CHECK(
				url.GetURL() == "http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title");
		}
		BOOST_AUTO_TEST_SUITE(GetURL_method)
			BOOST_AUTO_TEST_CASE(should_not_include_standard_ports_in_url)
			{
				CHttpUrl httpUrl("http://www.mysite.com:80/docs/document1.html?page=30&lang=en#title");
				BOOST_CHECK_EQUAL(httpUrl.GetURL(), 
					"http://www.mysite.com/docs/document1.html?page=30&lang=en#title");

				CHttpUrl httpsUrl("https://www.mysite.com:443/docs/document1.html?page=30&lang=en#title");
				BOOST_CHECK_EQUAL(httpsUrl.GetURL(), 
					"https://www.mysite.com/docs/document1.html?page=30&lang=en#title");

				CHttpUrl ftpUrl("ftp://www.mysite.com:21/docs/document1.html?page=30&lang=en#title");
				BOOST_CHECK_EQUAL(ftpUrl.GetURL(),
					"ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title");
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(is_case_insensitive)
	{
		BOOST_CHECK_NO_THROW(CHttpUrl url("wWW.mysite.COM", "docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 100));
		BOOST_CHECK_NO_THROW(CHttpUrl url("hTTp://www.mysite.cOm:80/docs/document1.html?page=30&lang=en#title"));
	}


BOOST_AUTO_TEST_SUITE_END()