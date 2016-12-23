#pragma once

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
	FTP = 21
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);

	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;
private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	std::string CHttpUrl::VerifiedDomain(std::string const & domain) const;
	std::string CHttpUrl::VerifiedDocument(std::string const & document) const;
	unsigned short VerifiedPort(int port) const;
	int GetPortFromStr(std::string const& portStr) const;
	Protocol GetProtocolFromStr(const std::string& protocol) const;
	std::string ConvertProtocol(Protocol const protocol) const;
};
