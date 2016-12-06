// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../HttpUrl/HttpUrl.h"

BOOST_AUTO_TEST_SUITE(Class_HttpUrl)

	BOOST_AUTO_TEST_CASE(can_be_constructed_from_input_parameters)
	{
		CHttpUrl test("domain", "document", HTTPS);
		BOOST_CHECK(true);
	}

	BOOST_AUTO_TEST_CASE(can_be_constructed_from_url_string)
	{
		CHttpUrl test("https://google.com/mail/index.html");
		BOOST_CHECK_EQUAL(test.GetPort(), 80);
		BOOST_CHECK_EQUAL(test.GetProtocol(), HTTPS);
	}
	BOOST_AUTO_TEST_SUITE(while_constructing)
		BOOST_AUTO_TEST_CASE(verify_domain)
		{
			CHttpUrl test("domain", "document", HTTPS);
			BOOST_CHECK(true);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct HttpUrlFixture
	{
		CHttpUrl test;
		HttpUrlFixture()
			: test("google.com", "/mail/index.html", HTTPS)
		{}

	
	};

	BOOST_FIXTURE_TEST_SUITE(after_construction, HttpUrlFixture)
		BOOST_AUTO_TEST_CASE(can_get_domain)
		{
			BOOST_CHECK_EQUAL(test.GetDomain(), "google.com");
		}
		BOOST_AUTO_TEST_CASE(can_get_document)
		{
			BOOST_CHECK_EQUAL(test.GetDocument(), "/mail/index.html");
		}
		BOOST_AUTO_TEST_CASE(can_get_protocol)
		{
			BOOST_CHECK_EQUAL(test.GetProtocol(), HTTPS);
		}
		BOOST_AUTO_TEST_CASE(can_get_port)
		{
			BOOST_CHECK_EQUAL(test.GetPort(), 80);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

