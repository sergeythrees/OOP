#pragma once
#include "stdafx.h"

enum Protocol {HTTP, HTTPS};

class CUrl
{
public:
	CUrl(string const& url);
	Protocol protocol();
	unsigned short port();
	string host();
	string document();

private:
	Protocol m_protocol = HTTP;
	unsigned short m_port = 80;
	string m_host;
	string m_document;
};