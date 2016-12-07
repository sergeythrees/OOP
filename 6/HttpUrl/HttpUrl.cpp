#include "stdafx.h"
#include <regex>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include "HttpUrl.h"

using namespace std;

CHttpUrl::CHttpUrl(std::string const & url)
	: m_domain("")
	, m_document("")
	, m_protocol(Protocol())
	, m_port(0)
	, m_isInitialized(false)
{
	regex urlRegex(regexLine);
	match_results<const char *> result;
	if (!(regex_search(url.c_str(), result, urlRegex)))
		m_isInitialized =  false; //throw incorrect url

		m_protocol = VerifiedProtocol(GetProtocolFromStr(std::string(result[1].first, result[1].second)));
		m_domain = VerifiedDomain(string(result[2].first, result[2].second));

		string portStr = std::string(result[3].first, result[3].second).c_str();
		unsigned short port = 0;
		if (portStr.empty())
			port = static_cast<unsigned short>(m_protocol);
		else
			port = static_cast<unsigned short>(stoi(portStr));
		m_port = VerifiedPort(port);

		m_document = VerifiedDocument(string(result[4].first, result[4].second));
		m_isInitialized = true;
		
}


CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
	: m_domain(VerifiedDomain(domain))
	, m_document(VerifiedDocument(document))
	, m_protocol(VerifiedProtocol(protocol))
	, m_port(VerifiedPort(port))
	, m_isInitialized(true)
{
}

std::string CHttpUrl::GetURL() const
{
	std::stringstream result = std::stringstream();
	result << ConvertProtocol(m_protocol) << "://" << m_domain;
	if (m_port != 80 && m_port != 443)
		result << ":" << m_port;
	result << m_document;
	return result.str();
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

bool CHttpUrl::IsInitialized()
{
	return m_isInitialized;
}

std::string CHttpUrl::VerifiedDomain(std::string const & domain) const
{
	return domain;
}

std::string CHttpUrl::VerifiedDocument(std::string const & document) const
{
	string result(document);
	if (document[0] != '/')
		result = "/" + document;
	return result;
}

Protocol CHttpUrl::VerifiedProtocol(Protocol const protocol) const
{
	return protocol;
}

unsigned short CHttpUrl::VerifiedPort(unsigned short const port) const
{
	if (!((port <= MAX_PORT_VAlUE) && (port >= MIN_PORT_VAlUE)))
	{
		// throw port is out of range
	}
	return port;
}

Protocol CHttpUrl::GetProtocolFromStr(std::string protocol) const
{
	Protocol resultProtocol = Protocol::HTTP;
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

std::string CHttpUrl::ConvertProtocol(Protocol const protocol) const
{
	string result;
	if (protocol == Protocol::HTTP)
	{
		result = "http";
	}
	else if (protocol == Protocol::HTTPS)
	{
		result = "https";
	}
	else if (protocol == Protocol::FTP)
	{
		result = "ftp";
	}
	return std::string();
}

string CHttpUrl::ToLower(string str) const
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}
