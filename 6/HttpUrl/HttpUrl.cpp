#include "stdafx.h"
#include <string>
#include <algorithm>
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
	: CHttpUrl::CHttpUrl(GetDomainFromStr(url), GetDocumentFromStr(url), GetProtocolFromStr(url))
{
	
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

std::string CHttpUrl::GetDomainFromStr(std::string const & str)
{
	return str;
}

std::string CHttpUrl::GetDocumentFromStr(std::string const & str)
{
	return str;
}

Protocol CHttpUrl::GetProtocolFromStr(std::string const & str)
{
	size_t foundPos = str.find("://");
	if (foundPos != str.npos)
	{
		string httpSubstr = ToLower(str.substr(0, foundPos));
		if (httpSubstr == "http")
		{
			return HTTP;
		}
		else if (httpSubstr == "https")
		{
			return HTTPS;
		}
	}
	throw invalid_argument("invalid protocol");
}

unsigned short CHttpUrl::GetPortFromStr(std::string const & str)
{
	string temp = str;
	return 0;
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

string CHttpUrl::ToLower(string str)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}
