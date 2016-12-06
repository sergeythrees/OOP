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
		cin >> urlString;
		if (urlString.empty())
		{
			continue;
		}
		CUrl url(urlString);
		if (url.IsInitialized())
		{
			cout << "HOST: " << url.host() << endl;
			cout << "PORT: " << url.port() << endl;
			cout << "DOC: " << url.document() << endl;
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
