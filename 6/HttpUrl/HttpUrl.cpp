#include "stdafx.h"
#include <map>
#include <regex>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "HttpUrl.h"
#include "CUrlParsingError.h"

static const int MAX_PORT_VALUE = 65535;
static const int MIN_PORT_VALUE = 1;
static const unsigned int REGEX_ELEMENTS_COUNT = 5;
static const std::string regexLine("(http|https|ftp)://([^/ :]+):?([^/ ]*)([^ ]*)");
static const std::map<std::string, Protocol> protocolStringMap = {
	{ "http", Protocol::HTTP },
	{ "https", Protocol::HTTPS },
	{ "ftp", Protocol::FTP }
};

using namespace std;

CHttpUrl::CHttpUrl(std::string const & url)
{
	regex urlRegex(regexLine);
	match_results<const char *> result;
	string urlLowerCase(boost::to_lower_copy(url));
	if (!(regex_search(urlLowerCase.c_str(), result, urlRegex)))
	{
		throw CUrlParsingError("Invalid URL line");
	}
	if (result.size() == REGEX_ELEMENTS_COUNT)
	{
		m_domain = VerifiedDomain(string(result[2].first, result[2].second));
		m_document = VerifiedDocument(string(result[4].first, result[4].second));
		m_protocol = GetProtocolFromStr(std::string(result[1].first, result[1].second));
		m_port = GetPortFromStr(string(result[3].first, result[3].second));
	}
	else
	{
		throw CUrlParsingError("Invalid regex");
	}
	
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
	catch (const out_of_range&)
	{
		throw CUrlParsingError("Port value is out of integer range");
	}
	catch (invalid_argument&)
	{
		throw CUrlParsingError("Port value is not integer");
	}

	return VerifiedPort(port);
}

Protocol CHttpUrl::GetProtocolFromStr(const std::string& protocol) const
{
	Protocol resultProtocol = Protocol::HTTP;
	if (!protocol.empty())
	{
		try
		{ 
			resultProtocol = protocolStringMap.at(boost::to_lower_copy(protocol));
		}
		catch (out_of_range&)
		{
			throw CUrlParsingError("Protocol value is incorrect");
		}
	}

	return resultProtocol;
}

std::string CHttpUrl::ConvertProtocol(Protocol const protocol) const
{
	string result;
	
	for (auto current : protocolStringMap)
		if (current.second == protocol)
			result = current.first;

	return result;
}
