#include "stdafx.h"
#include <map>
#include <regex>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "HttpUrl.h"

using namespace std;

namespace
{
	static const int MAX_PORT_VALUE = 65535;
	static const int MIN_PORT_VALUE = 1;
	static const unsigned int REGEX_ELEMENTS_COUNT = 5;
	static const std::string regexLine("(http|https|ftp)://([^/ :]+):?([^/ ]*)([^ ]*)");
	static const std::map<Protocol, std::string> protocolStringMap = {
		{ Protocol::HTTP, "http" },
		{ Protocol::HTTPS, "https" },
		{ Protocol::FTP, "ftp" }
	};
}

CHttpUrl::CHttpUrl(std::string const & url)
{
	regex urlRegex(regexLine);
	match_results<const char *> result;
	string urlLowerCase(boost::to_lower_copy(url));
	if (!(regex_search(urlLowerCase.c_str(), result, urlRegex)))
	{
		throw invalid_argument("Invalid URL line");
	}
	if (result.size() == REGEX_ELEMENTS_COUNT)
	{
		m_domain = string(result[2].first, result[2].second);
		m_document = string(result[4].first, result[4].second);
		m_protocol = GetProtocolFromStr(std::string(result[1].first, result[1].second));
		m_port = GetPortFromStr(string(result[3].first, result[3].second));
	}
	else
	{
		throw invalid_argument("Invalid regex");
	}

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

unsigned short CHttpUrl::VerifiedPort(int const port) const
{
	if ((port <= MAX_PORT_VALUE) && (port >= MIN_PORT_VALUE))
	{
		return static_cast<unsigned short>(port);
	}
	stringstream mess;
	mess << "Port value is out of port allow range (" << MIN_PORT_VALUE << ".." << MAX_PORT_VALUE << ")";
	throw invalid_argument(mess.str());
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
		throw invalid_argument("Port value is out of integer range");
	}
	catch (const invalid_argument&)
	{
		throw invalid_argument("Port value is not integer");
	}

	return VerifiedPort(port);
}

Protocol CHttpUrl::GetProtocolFromStr(const std::string& protocol) const
{
	Protocol result = Protocol::HTTP;
	if (!protocol.empty())
		for (auto current : protocolStringMap)
			if (current.second == protocol)
				result = current.first;

	return result;
}