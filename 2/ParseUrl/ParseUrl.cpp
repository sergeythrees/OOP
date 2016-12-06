#include "stdafx.h"
#include "ParseUrl.h"

using namespace std;

CUrl::CUrl(string const & url)
	: m_protocol()
	, m_port()
	, m_host()
	, m_document()
{
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
