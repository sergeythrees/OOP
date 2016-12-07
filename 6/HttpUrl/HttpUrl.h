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
		Protocol protocol = Protocol::HTTP,
		unsigned short port = 80);

	// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
	// выбранного протокола (80 дл€ http и 443 дл€ https) в URL не должен включатьс€
	std::string GetURL() const;

	// возвращает доменное им€
	std::string GetDomain() const;

	/*
	¬озвращает им€ документа. ѕримеры:
	/
	/index.html
	/images/photo.jpg
	*/
	std::string GetDocument() const;

	// возвращает тип протокола
	Protocol GetProtocol() const;

	// возвращает номер порта
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
