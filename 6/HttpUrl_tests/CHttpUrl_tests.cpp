#include "stdafx.h"
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/variant.hpp>
#include "../HttpUrl/HttpUrl.h"
#include "../HttpUrl/CUrlParsingError.h"

using namespace std;
using namespace boost;

template <typename Ex, typename Fn>
void ExpectException(Fn && fn, const string & expectedDescription)
{
	try
	{

	fn(); // Выполняем действие, от которого ожидаем выброс исключения
	// Если не выбросило, то тест провалился
	BOOST_ERROR("No exception thrown");
	}
	catch (const Ex & e) // Ловим исключение типа Ex (или его подкласс)
	{
	// Проверяем, что исключение будет иметь ожидаемое сообщение
	BOOST_CHECK_EQUAL(expectedDescription, e.what());
	}
	catch (...)
	{
	// Если выбросили иное исключение, то это также ошибка
	BOOST_ERROR("Unexpected exception");
	}
	
}

struct CHttpUrlParameters
{
	std::string domain;
	std::string document;
	optional<Protocol> protocol;
	optional<unsigned short> port;
};

void ExpectCHttpUrlParameters(const CHttpUrlParameters& result, const CHttpUrlParameters& expected)
{
	BOOST_CHECK_EQUAL(result.domain, expected.domain);
	BOOST_CHECK_EQUAL(result.document, expected.document);
	if (result.port.is_initialized())
		BOOST_CHECK_EQUAL(result.port, expected.port.get());
	if (result.protocol.is_initialized())
		BOOST_CHECK(result.protocol == expected.protocol.get());

}

void ExpectCHttpUrl(variant<string, CHttpUrlParameters> parameters, optional<const CHttpUrlParameters> expected)
{
	optional<CHttpUrl> url;
	if (parameters.type() == typeid(string))
	{
		BOOST_CHECK_NO_THROW(url = CHttpUrl(get<string>(parameters)));
		ExpectCHttpUrlParameters({ url.get().GetDomain(), url.get().GetDocument(), url.get().GetProtocol(), url.get().GetPort() }, expected.get());
	}
	else if (parameters.type() == typeid(CHttpUrlParameters))
	{
		CHttpUrlParameters p = get<CHttpUrlParameters>(parameters);
		if (p.port.is_initialized())
		{
			BOOST_CHECK_NO_THROW(url = CHttpUrl(p.domain, p.document.c_str() + 1, p.protocol.get(), p.port.get()));
			ExpectCHttpUrlParameters({ url.get().GetDomain(), url.get().GetDocument(), url.get().GetProtocol(), url.get().GetPort() }, p);
		}
		else if (!p.port.is_initialized() && !p.protocol.is_initialized())
		{
			BOOST_CHECK_NO_THROW(url = CHttpUrl(p.domain, p.document.c_str() + 1));
			ExpectCHttpUrlParameters({ url.get().GetDomain(), url.get().GetDocument()}, p);
		}
		else
		{
			BOOST_CHECK_NO_THROW(url = CHttpUrl(p.domain, p.document.c_str() + 1, p.protocol.get()));
			ExpectCHttpUrlParameters({ url.get().GetDomain(), url.get().GetDocument(), url.get().GetProtocol()}, p);
		}
		
	}

	
		
}

BOOST_AUTO_TEST_SUITE(HttpUrl_class)

	BOOST_AUTO_TEST_SUITE(constructor_from_string)
		BOOST_AUTO_TEST_CASE(can_be_costruct_from_correct_url_string)
		{
			ExpectCHttpUrl("http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title", 
				CHttpUrlParameters({ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" , Protocol::HTTP, 100 }));
		}
		BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_line_without_port_value)
		{
			ExpectCHttpUrl("http://www.mysite.com/docs/document1.html?page=30&lang=en#title", 
				CHttpUrlParameters({ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" , Protocol::HTTP, 80 }));
		}
		BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_line_with_other_protocols)
		{
			ExpectCHttpUrl("https://www.mysite.com/docs/document1.html?page=30&lang=en#title",
				CHttpUrlParameters({ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" , Protocol::HTTPS, 443}));

			ExpectCHttpUrl("ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title",
				CHttpUrlParameters({ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" , Protocol::FTP, 21 }));
		}
		BOOST_AUTO_TEST_SUITE(should_return_approppriate_exceptions)
			BOOST_AUTO_TEST_CASE(when_can_not_parse_URL_line)
			{
				ExpectException<invalid_argument>([]() {
					CHttpUrl(""); },
					"Invalid URL line");
				ExpectException<invalid_argument>([]() {
					CHttpUrl("http:/ur"); },
					"Invalid URL line");
				ExpectException<invalid_argument>([]() {
					CHttpUrl("http:///"); },
					"Invalid URL line");
			}
			BOOST_AUTO_TEST_CASE(when_port_value_is_out_of_integer_range)
			{
				ExpectException<invalid_argument>([]() {
					CHttpUrl("http://ur.ru:2222222222/"); },
					"Port value is out of integer range");
			}
			BOOST_AUTO_TEST_CASE(when_port_value_is_out_of_port_allow_range)
			{
				ExpectException<invalid_argument>([]() {
					CHttpUrl("http://ur.ru:-1/"); },
					"Port value is out of port allow range (1..65535)");
				ExpectException<invalid_argument>([]() {
					CHttpUrl("http://ur.ru:0/"); },
					"Port value is out of port allow range (1..65535)");
				ExpectException<invalid_argument>([]() {
					CHttpUrl("http://ur.ru:65536/"); },
					"Port value is out of port allow range (1..65535)");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(constructor_from_parameters)
		BOOST_AUTO_TEST_CASE(can_be_construct_from_correct_parameters)
		{
			ExpectCHttpUrl(CHttpUrlParameters({ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" , Protocol::HTTP, 100 }), none);
		}
		BOOST_AUTO_TEST_CASE(can_be_construct_without_port_value)
		{
			ExpectCHttpUrl(CHttpUrlParameters({ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title", Protocol::HTTP }), none);
		}
		BOOST_AUTO_TEST_CASE(can_be_construct_without_port_and_protocol_value)
		{
			ExpectCHttpUrl(CHttpUrlParameters({ "www.mysite.com", "/docs/document1.html?page=30&lang=en#title" }), none);
		}
		BOOST_AUTO_TEST_SUITE(should_return_approppriate_exceptions)
			BOOST_AUTO_TEST_CASE(when_parameters_are_incorrect)
			{
				ExpectException<invalid_argument>([]() {
					CHttpUrl("", "/index.html"); },
					"Domain must not be empty");
			}
			BOOST_AUTO_TEST_CASE(when_port_value_is_out_of_port_allow_range)
			{
				ExpectException<invalid_argument>([]() {
					CHttpUrl("mysite.com", "/index.html", Protocol::HTTP, 0); },
					"Port value is out of port allow range (1..65535)");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()


	struct HttpUrlFixture
	{
		CHttpUrl url;
		HttpUrlFixture()
			: url("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 100)
		{}


	};

	BOOST_FIXTURE_TEST_SUITE(after_construction, HttpUrlFixture)

		BOOST_AUTO_TEST_CASE(can_get_domain)
		{
			BOOST_CHECK_EQUAL(url.GetDomain(), "www.mysite.com");
		}

		BOOST_AUTO_TEST_CASE(can_get_document)
		{
			BOOST_CHECK_EQUAL(url.GetDocument(), "/docs/document1.html?page=30&lang=en#title");
		}

		BOOST_AUTO_TEST_CASE(can_get_protocol)
		{
			BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
		}

		BOOST_AUTO_TEST_CASE(can_get_port)
		{
			BOOST_CHECK_EQUAL(url.GetPort(), 100);
		}

		BOOST_AUTO_TEST_SUITE(GetURL_method)
			BOOST_AUTO_TEST_CASE(can_get_url_string)
			{
				BOOST_CHECK(url.GetURL() == "http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title");
			}
			BOOST_AUTO_TEST_CASE(should_not_include_standart_ports_in_url)
			{
				CHttpUrl httpUrl("http://www.mysite.com:80/docs/document1.html?page=30&lang=en#title");
				BOOST_CHECK_EQUAL(httpUrl.GetURL(), "http://www.mysite.com/docs/document1.html?page=30&lang=en#title");

				CHttpUrl httpsUrl("https://www.mysite.com:443/docs/document1.html?page=30&lang=en#title");
				BOOST_CHECK_EQUAL(httpsUrl.GetURL(), "https://www.mysite.com/docs/document1.html?page=30&lang=en#title");
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()