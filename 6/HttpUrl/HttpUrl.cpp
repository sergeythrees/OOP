#include "stdafx.h"
#include <regex>
#include <boost/algorithm/string.hpp>
#include <sstream>
#include "HttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

CHttpUrl::CHttpUrl(std::string const & url)
{
	regex urlRegex(regexLine);
	match_results<const char *> result;
	string urlLowerCase(ToLower(url));
	if (!(regex_search(urlLowerCase.c_str(), result, urlRegex)))
	{
		throw CUrlParsingError("Invalid URL line");
	}

	m_domain = VerifiedDomain(string (result[2].first, result[2].second));
	m_document = VerifiedDocument(string(result[4].first, result[4].second));
	m_protocol = GetProtocolFromStr(std::string(result[1].first, result[1].second));
	m_port = GetPortFromStr(string(result[3].first, result[3].second));		
}


CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol, unsigned short port)
	: m_domain(VerifiedDomain(domain))
	, m_document(VerifiedDocument(document))
	, m_protocol(protocol)
	, m_port(VerifiedPort(port)) 
{
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document, Protocol protocol)
	: CHttpUrl::CHttpUrl(domain, document, protocol, static_cast<unsigned short>(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const & domain, std::string const & document)
	: CHttpUrl::CHttpUrl(domain, document, Protocol::HTTP)
{
}

std::string CHttpUrl::GetURL() const
{
	std::stringstream result = std::stringstream();
	result << ConvertProtocol(m_protocol) << "://" << m_domain;
	if (m_port != static_cast<unsigned short>(Protocol::HTTP) &&
		m_port != static_cast<unsigned short>(Protocol::HTTPS) &&
		m_port != static_cast<unsigned short>(Protocol::FTP))
	{
		result << ":" << m_port;
	}
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

std::string CHttpUrl::VerifiedDomain(std::string const & domain) const
{
	if (domain.empty())
		throw invalid_argument("Domain must not be empty");
	return domain;
}

std::string CHttpUrl::VerifiedDocument(std::string const & document) const
{
	string result(document);
	if (document[0] != '/' && !document.empty())
		result = "/" + document;
	return result;
}

unsigned short CHttpUrl::VerifiedPort(int const port) const
{
	if ((port <= MAX_PORT_VALUE) && (port >= MIN_PORT_VALUE))
	{
		return static_cast<unsigned short>(port);
	}
	stringstream mess;
	mess << "Port value is out of port allow range (" << MIN_PORT_VALUE << ".." << MAX_PORT_VALUE << ")";
	throw CUrlParsingError(mess.str());
}

unsigned short CHttpUrl::GetPortFromStr(string const & portStr) const
{
	int port = 0;
	if (portStr.empty())
	{
		return static_cast<unsigned short>(m_protocol);
	}
	else try
	{
		port = stoi(portStr);
	}
	catch (out_of_range&)
	{
		throw CUrlParsingError("Port value is out of integer range");
	}

	return VerifiedPort(port);
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
	return result;
}

string CHttpUrl::ToLower(string str) const
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return str;
}
