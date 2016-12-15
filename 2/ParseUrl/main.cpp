#include "stdafx.h"
#include "HttpUrl.h"

using namespace std;

void ParseURLsFromStream(istream& input, ostream& output)
{
	string urlString;
	while (!input.eof())
	{
		output << "URL: ";
		input >> urlString;
		if (urlString.empty())
		{
			continue;
		}
		try
		{
			CHttpUrl url(urlString);
			output << "HOST: " << url.GetDomain() << endl;
			output << "PORT: " << url.GetPort() << endl;
			output << "DOC: " << url.GetDocument() << endl;
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