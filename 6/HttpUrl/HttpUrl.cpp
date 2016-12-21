#include "stdafx.h"
#include <map>
#include <regex>
#include <sstream>
#include <assert.h>
#include <boost/assign.hpp>
#include <boost/bimap.hpp>
#include <boost/algorithm/string.hpp>
#include "HttpUrl.h"
#include "CUrlParsingError.h"

static const int MAX_PORT_VALUE = 65535;
static const int MIN_PORT_VALUE = 1;
static const unsigned int REGEX_ELEMENTS_COUNT = 6;
static const std::string regexLine("(http|https|ftp)://([^/:]*)(:([^/]*))*(/[^\\0]*)*");

static const boost::bimap<Protocol, std::string> protocolStringMap 
	= boost::assign::list_of<boost::bimap<Protocol, std::string>::relation >
		(Protocol::HTTP, "http")
		(Protocol::HTTPS, "https")
		( Protocol::FTP, "ftp");

using namespace std;

CHttpUrl::CHttpUrl(std::string const & url) 
{
	regex urlRegex(regexLine.c_str());
	match_results<const char *> result;
	string urlLowerCase(boost::to_lower_copy(url));
	if (!regex_match(urlLowerCase, urlRegex))
	{
		throw CUrlParsingError("Invalid URL line");
	}
	regex_search(urlLowerCase.c_str(), result, urlRegex);
	assert(result.size() == REGEX_ELEMENTS_COUNT);
	m_protocol = GetProtocolFromStr(std::string(result[1].first, result[1].second));
	m_domain = VerifiedDomain(string(result[2].first, result[2].second));
	m_port = VerifiedPort(GetPortFromStr(string(result[4].first, result[4].second)));
	m_document = VerifiedDocument(string(result[5].first, result[5].second));
	
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
	if (!protocolStringMap.left.count(static_cast<Protocol>(m_port)))
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
	else if (domain.find_first_of(" \t/\\") != domain.npos)
	{
		throw invalid_argument("Domain should not contains any spaces, tabulations or slashes");
	}
	return domain;
}

std::string CHttpUrl::VerifiedDocument(std::string const & document) const
{
	string result(document);
	if (document.find_first_of(" \t") != document.npos)
	{
		throw invalid_argument("Document should not contains spaces or tabulations");
	}
	if (document[0] != '/')
		result = "/" + document;

	return result;
}

unsigned short CHttpUrl::VerifiedPort(int port) const
{
	if (port < MIN_PORT_VALUE || port > MAX_PORT_VALUE)
	{
		stringstream mess;
		mess << "Port value is out of port allow range (" << MIN_PORT_VALUE << ".." << MAX_PORT_VALUE << ")";
		throw CUrlParsingError(mess.str());
	}
	return static_cast<unsigned short>(port);
}

int CHttpUrl::GetPortFromStr(string const & portStr) const
{
	int port = 0;
	if (portStr.empty())
	{
		return static_cast<int>(m_protocol);
	}
	else try
	{
		if (portStr.find_first_not_of("0123456789") != portStr.npos)
			throw invalid_argument("");
		else
			port = stoi(portStr);
	}
	catch (const out_of_range&)
	{
		throw CUrlParsingError("Port value is out of integer range");
	}
	catch (const invalid_argument&)
	{
		throw CUrlParsingError("Port value is not a number");
	}

	return port;
}

Protocol CHttpUrl::GetProtocolFromStr(const std::string& protocol) const
{
	Protocol result = Protocol::HTTP;
	if (!protocol.empty())
	{
		result = protocolStringMap.right.at(protocol);
	}

	return result;
}

std::string CHttpUrl::ConvertProtocol(Protocol const protocol) const
{
	string result = protocolStringMap.left.at(protocol);

	return result;
}
