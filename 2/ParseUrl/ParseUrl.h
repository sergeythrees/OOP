#pragma once
#include "stdafx.h"

static const int MAX_PORT_VAlUE = 65535;
static const int MIN_PORT_VAlUE = 1;

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
	FTP = 21
};

class CUrl
{
public:
	CUrl(const std::string& url);
	Protocol protocol();
	unsigned short port();
	std::string host();
	std::string document();
	bool IsInitialized();

private:
	Protocol m_protocol;
	unsigned short m_port;
	std::string m_host;
	std::string m_document;
	bool m_isInitialized;

	Protocol GetProtocolFromStr(std::string protocol);
};