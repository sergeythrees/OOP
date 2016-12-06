#include "stdafx.h"
#include <regex>
#include <boost/algorithm/string.hpp>
#include "HttpUrl.h"

using namespace std;

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
	: m_domain(VerifiedDomain(domain))
	, m_document(VerifiedDocument(document))
	, m_protocol(VerifiedProtocol(protocol))
	, m_port(VerifiedPort(port))
{
}

CHttpUrl::CHttpUrl(std::string const & url)
	: m_domain()
	, m_document()
	, m_protocol()
	, m_port()
{
	regex urlRegex(regexLine);
	match_results<const char *> result;
	if (regex_search(url.c_str(), result, urlRegex))
	{
		Protocol protocol = GetProtocolFromStr(std::string(result[1].first, result[1].second));
		string host = std::string(result[2].first, result[2].second);

		string portStr = std::string(result[3].first, result[3].second).c_str();
		unsigned short port;
		if (portStr.empty())
			port = static_cast<unsigned short>(protocol);
		else
			port = stoi(portStr);

		string document = std::string(result[4].first, result[4].second);

		if ((port <= MAX_PORT_VAlUE) && (port >= MIN_PORT_VAlUE))
		{
			m_protocol = protocol;
			m_domain = host;
			m_port = port;
			m_document = document;
			//m_isInitialized = true;
		}
	}
}

std::string CHttpUrl::GetURL() const
{
	return std::string();
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::VerifiedDomain(std::string const & domain)
{
	return domain;
}

std::string CHttpUrl::VerifiedDocument(std::string const & document)
{
	return document;
}

Protocol CHttpUrl::VerifiedProtocol(Protocol const protocol)
{
	return protocol;
}

unsigned short CHttpUrl::VerifiedPort(unsigned short const port)
{
	return port;
}

Protocol CHttpUrl::GetProtocolFromStr(std::string protocol)
{
	Protocol resultProtocol;
	boost::to_lower(protocol);
	if (protocol == "http")
	{
		resultProtocol = Protocol::HTTP;
	}
	else if (protocol == "https")
	{
		resultProtocol = Protocol::HTTPS;
	}
	else if (protocol == "ftp")
	{
		resultProtocol = Protocol::FTP;
	}
	return resultProtocol;
}

string CHttpUrl::ToLower(string str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}
