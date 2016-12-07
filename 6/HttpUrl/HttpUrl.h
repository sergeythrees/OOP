#pragma once

static const int MAX_PORT_VAlUE = 65535;
static const int MIN_PORT_VAlUE = 1;
static const std::string regexLine("(http|https|ftp)://([^/ :]+):?([^/ ]*)/([^ ]*)");

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
	FTP = 21
};

class CHttpUrl
{
public:
	// ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
	// ���������� ���������� CUrlParsingError, ���������� ��������� �������� ������
	CHttpUrl(std::string const& url);

	/* �������������� URL �� ������ ���������� ����������.
	��� �������������� ������� ���������� ����������� ����������
	invalid_argument
	���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP,
		unsigned short port = 80);

	// ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
	// ���������� ��������� (80 ��� http � 443 ��� https) � URL �� ������ ����������
	std::string GetURL() const;

	// ���������� �������� ���
	std::string GetDomain() const;

	/*
	���������� ��� ���������. �������:
	/
	/index.html
	/images/photo.jpg
	*/
	std::string GetDocument() const;

	// ���������� ��� ���������
	Protocol GetProtocol() const;

	// ���������� ����� �����
	unsigned short GetPort() const;

	bool IsInitialized();
private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
	bool m_isInitialized = false;

	std::string VerifiedDomain(std::string const& domain) const;
	std::string VerifiedDocument(std::string const& document) const;
	Protocol VerifiedProtocol(Protocol const protocol) const;
	unsigned short VerifiedPort(unsigned short const port) const;
	Protocol GetProtocolFromStr(std::string protocol) const;
	std::string ConvertProtocol(Protocol const protocol) const;
	std::string ToLower(std::string str) const;
};
