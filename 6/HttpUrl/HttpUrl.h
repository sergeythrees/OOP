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
	// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
	ѕри недопустимости входных параметров выбрасывает исключение
	invalid_argument
	≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol);
	CHttpUrl(
		std::string const& domain,
		std::string const& document);

	std::string GetURL() const;
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
	unsigned short VerifiedPort(int const port) const;
	unsigned short GetPortFromStr(std::string const &portStr) const;
	Protocol GetProtocolFromStr(std::string protocol) const;
	std::string ConvertProtocol(Protocol const protocol) const;
	std::string ToLower(std::string str) const;
};
