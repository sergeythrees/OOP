#include "stdafx.h"
#include <regex>
#include <boost/algorithm/string.hpp>
#include "ParseUrl.h"

using namespace std;

namespace
{
	static const std::string regexLine("(http|https|ftp)://([^/ :]+):?([^/ ]*)/([^ ]*)");
}

CUrl::CUrl(const std::string & url)
	: m_protocol()
	, m_port(static_cast<unsigned short>(Protocol::HTTP))
	, m_host()
	, m_document()
	, m_isInitialized(false)
{
	regex urlRegex(regexLine);
	match_results<const char *> result;
	if (regex_search(url.c_str(), result, urlRegex))
	{
		Protocol protocol = GetProtocolFromStr(std::string(result[1].first, result[1].second));
		string host = std::string(result[2].first, result[2].second);

		string portStr = std::string(result[3].first, result[3].second).c_str();
		int port;
		if (portStr.empty())
			port = static_cast<int>(protocol);
		else
		{
			try
			{
				port = stoi(portStr);
			}
			catch (const std::out_of_range&)
			{
				throw std::out_of_range("Port value is out of range ");
			}
		}
			

		string document = std::string(result[4].first, result[4].second);

		if ((port <= MAX_PORT_VAlUE) && (port >= MIN_PORT_VAlUE))
		{
			m_protocol = protocol;
			m_host = host;
			m_port = port;
			m_document = document;
			m_isInitialized = true;
		}
		else
			throw std::out_of_range("Port value is out of range ");
	}
}

Protocol CUrl::protocol()
{
	return m_protocol;
}

unsigned short CUrl::port()
{
	return m_port;
}

string CUrl::host()
{
	return m_host;
}

string CUrl::document()
{
	return m_document;
}

bool CUrl::IsInitialized()
{
	return m_isInitialized;
}

Protocol CUrl::GetProtocolFromStr(std::string protocol)
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