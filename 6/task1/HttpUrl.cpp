#include "stdafx.h"
#include <string>
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
	: CHttpUrl::CHttpUrl(GetDomainFromStr(url), GetDocumentFromStr(url), GetProtocolFromStr(url), GetPortFromStr(url))
{
	
}

std::string CHttpUrl::GetURL() const
{
	return std::string();
}

std::string CHttpUrl::GetDomain() const
{
	return std::string();
}

std::string CHttpUrl::GetDocument() const
{
	return std::string();
}

Protocol CHttpUrl::GetProtocol() const
{
	return Protocol();
}

unsigned short CHttpUrl::GetPort() const
{
	return 0;
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
	string temp = str;
	return Protocol();
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
