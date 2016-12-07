// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../HttpUrl/HttpUrl.h"

BOOST_AUTO_TEST_SUITE(HttpUrl_class)

	BOOST_AUTO_TEST_CASE(can_be_costruct_from_input_arguments)
	{
		CHttpUrl url("www.mysite.com", "docs/document1.html?page=30&lang=en#title", Protocol::HTTP, 100);
		BOOST_CHECK(url.IsInitialized());
		BOOST_CHECK_EQUAL(url.GetPort(), 100);
		BOOST_CHECK_EQUAL(url.GetDomain(), "www.mysite.com");
		BOOST_CHECK_EQUAL(url.GetDocument(), "/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(url.GetProtocol() == Protocol::HTTP);
	}
	
	BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_string)
	{
		CHttpUrl url("http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(url.IsInitialized());
		BOOST_CHECK_EQUAL(url.GetPort(), 100);
	}

	BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_without_port_value)
	{
		CHttpUrl url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(url.IsInitialized());
		BOOST_CHECK_EQUAL(url.GetPort(), 80);
	}

	BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_with_other_protocol)
	{
		CHttpUrl httpsUrl("https://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(httpsUrl.IsInitialized());
		BOOST_CHECK(httpsUrl.GetProtocol() == Protocol::HTTPS);

		CHttpUrl ftpUrl("ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(ftpUrl.IsInitialized());
		BOOST_CHECK(ftpUrl.GetProtocol() == Protocol::FTP);
	}

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
				CHttpUrl httpUrl("https://www.mysite.com:80/docs/document1.html?page=30&lang=en#title");
				BOOST_CHECK(httpUrl.IsInitialized());
				BOOST_CHECK(httpUrl.GetURL() == "https://www.mysite.com/docs/document1.html?page=30&lang=en#title");

				CHttpUrl httpsUrl("https://www.mysite.com:443/docs/document1.html?page=30&lang=en#title");
				BOOST_CHECK(httpsUrl.IsInitialized());
				BOOST_CHECK(httpsUrl.GetURL() == "https://www.mysite.com/docs/document1.html?page=30&lang=en#title");
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

