#include "stdafx.h"
#include "HttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

void ParseURLsFromStream(istream& input, ostream& output)
{
	string urlString;
	while (!input.eof())
	{
		output << "   > ";
		getline(input, urlString);
		if (urlString.empty())
		{
			continue;
		}
		try 
		{
			CHttpUrl url(urlString);
			output
				<< "URL: " << url.GetURL() << endl
				<< "HOST: " << url.GetDomain() << endl
				<< "PORT: " << url.GetPort() << endl
				<< "DOC: " << url.GetDocument() << endl;
		}
		catch (const invalid_argument &ex)
		{
			cerr << ex.what() << endl;
		}
		output << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Для завершения введите Ctrl-Z" << endl;
	ParseURLsFromStream(cin, cout);
	return EXIT_SUCCESS;
}

