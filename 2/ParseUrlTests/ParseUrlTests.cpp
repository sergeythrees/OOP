#include "stdafx.h"
#include "../ParseUrl/ParseUrl.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ParseUrl_class)

	BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_string)
	{
		CUrl url("http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(url.IsInitialized());
		BOOST_CHECK_EQUAL(url.port(), 100);
	}
	
	BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_without_port_value)
	{
		CUrl url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(url.IsInitialized());
		BOOST_CHECK_EQUAL(url.port(), 80);
	}

	BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_with_other_protocol)
	{
		CUrl httpsUrl("https://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(httpsUrl.IsInitialized());
		BOOST_CHECK(httpsUrl.protocol() == Protocol::HTTPS);

		CUrl ftpUrl("ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(ftpUrl.IsInitialized());
		BOOST_CHECK(ftpUrl.protocol() == Protocol::FTP);
	}

	BOOST_AUTO_TEST_CASE(must_not_be_initialized_from_incorrect_url_line)
	{
		CUrl crashedUrl("http:/www.mysite.com:100/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(!crashedUrl.IsInitialized());

		CUrl emptyUrl("");
		BOOST_CHECK(!emptyUrl.IsInitialized());
	}

	BOOST_AUTO_TEST_CASE(must_not_be_initialized_if_port_value_is_out_of_range)
	{
		CUrl urlWithZeroProtocol("http://www.mysite.com:0/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(!urlWithZeroProtocol.IsInitialized());

		CUrl urlWithVeryBigProtocol("http://www.mysite.com:65536/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(!urlWithVeryBigProtocol.IsInitialized());
	}
BOOST_AUTO_TEST_SUITE_END()