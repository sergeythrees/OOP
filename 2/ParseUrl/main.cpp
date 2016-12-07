#include "stdafx.h"
#include "ParseUrl.h"

const unsigned ARG_COUNT = 2;

using namespace std;

void ParseUrlFromStream()
{
	string urlString;
	while (!cin.eof())
	{
		cout << "URL: ";
		try
		{
			cin >> urlString;
			if (urlString.empty())
				throw std::invalid_argument("URL should not empty");

			CUrl url(urlString);
			if (url.IsInitialized())
			{
				cout << "HOST: " << url.host() << endl;
				cout << "PORT: " << url.port() << endl;
				cout << "DOC: " << url.document() << endl;
			}
		}
		catch (const std::exception& except)
		{
			std::cerr << except.what() << endl;
		}
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Для завершения введите Ctrl-Z" << endl;
	ParseUrlFromStream();
	return EXIT_SUCCESS;
}
