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
	try
	{
		fn();
		BOOST_ERROR("No exception thrown");
	}
	catch (const Ex & e)
	{
		BOOST_CHECK_EQUAL(expectedDescription, e.what());
	}
	catch (...)
	{
		BOOST_ERROR("Unexpected exception");
	}
	
}

struct UrlParams
{
	std::string domain;
	std::string document;
	optional<Protocol> protocol;
	optional<unsigned short> port;
};

void VerifyUrlParams(const UrlParams& result, const UrlParams& expected)
{
	BOOST_CHECK_EQUAL(result.domain, expected.domain);
	BOOST_CHECK_EQUAL(result.document, expected.document);
	if (result.port.is_initialized())
		BOOST_CHECK_EQUAL(result.port, expected.port.get());
	if (result.protocol.is_initialized())
		BOOST_CHECK(result.protocol == expected.protocol.get());

}

void VerifyCHttpUrl(variant<string, UrlParams> parameters, optional<const UrlParams> expected)
{
	optional<CHttpUrl> url;
	if (parameters.type() == typeid(string))
	{
		BOOST_CHECK_NO_THROW(url = CHttpUrl(get<string>(parameters)));
		VerifyUrlParams(
			{ url.get().GetDomain(), url.get().GetDocument(), url.get().GetProtocol(), url.get().GetPort() }, 
			expected.get());
	}
	else if (parameters.type() == typeid(UrlParams))
	{
		UrlParams p = get<UrlParams>(parameters);
		if (p.port.is_initialized())
		{
			BOOST_CHECK_NO_THROW(url = CHttpUrl(p.domain, p.document.c_str() + 1, p.protocol.get(), p.port.get()));
			VerifyUrlParams(
				{ url.get().GetDomain(), url.get().GetDocument(), url.get().GetProtocol(), url.get().GetPort() }, 
				p);
		}
		else if (!p.port.is_initialized() && !p.protocol.is_initialized())
		{
			BOOST_CHECK_NO_THROW(url = CHttpUrl(p.domain, p.document.c_str() + 1));
			VerifyUrlParams({ url.get().GetDomain(), url.get().GetDocument()}, p);
		}
		else
		{
			BOOST_CHECK_NO_THROW(url = CHttpUrl(p.domain, p.document.c_str() + 1, p.protocol.get()));
			VerifyUrlParams({ url.get().GetDomain(), url.get().GetDocument(), url.get().GetProtocol()}, p);
		}
		
	}	
		
}

BOOST_AUTO_TEST_SUITE(HttpUrl_class)

	BOOST_AUTO_TEST_SUITE(constructor_from_string)
		BOOST_AUTO_TEST_CASE(can_be_costruct_from_correct_url_string)
		{
			VerifyCHttpUrl("http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title", UrlParams(
				{ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" , Protocol::HTTP, 100 }));
		}
		BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_line_without_port_value)
		{
			VerifyCHttpUrl("http://www.mysite.com/docs/document1.html?page=30&lang=en#title", UrlParams(
				{ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" , Protocol::HTTP, 80 }));
		}
		BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_line_with_other_protocols)
		{
			VerifyCHttpUrl("https://www.mysite.com/docs/document1.html?page=30&lang=en#title", UrlParams(
				{ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" , Protocol::HTTPS, 443}));

			VerifyCHttpUrl("ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title", UrlParams(
				{ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" , Protocol::FTP, 21 }));
		}
		BOOST_AUTO_TEST_SUITE(should_return_approppriate_exceptions)
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
		BOOST_AUTO_TEST_CASE(can_be_construct_from_correct_parameters)
		{
			VerifyCHttpUrl(UrlParams(
				{ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" , Protocol::HTTP, 100 }), 
				none);
		}
		BOOST_AUTO_TEST_CASE(can_be_construct_without_port_value)
		{
			VerifyCHttpUrl(UrlParams(
				{ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP }), 
				none);
		}
		BOOST_AUTO_TEST_CASE(can_be_construct_without_port_and_protocol_value)
		{
			VerifyCHttpUrl(UrlParams(
				{ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" }), 
				none);
		}
		BOOST_AUTO_TEST_SUITE(should_return_approppriate_exceptions)
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
			BOOST_AUTO_TEST_CASE(should_not_include_standart_ports_in_url)
			{
				CHttpUrl httpUrl("http://www.mysite.com:80/docs/document1.html?page=30&lang=en#title");
				BOOST_CHECK_EQUAL(httpUrl.GetURL(), 
					"http://www.mysite.com/docs/document1.html?page=30&lang=en#title");

				CHttpUrl httpsUrl("https://www.mysite.com:443/docs/document1.html?page=30&lang=en#title");
				BOOST_CHECK_EQUAL(httpsUrl.GetURL(), 
					"https://www.mysite.com/docs/document1.html?page=30&lang=en#title");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()