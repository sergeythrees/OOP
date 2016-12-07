#include "stdafx.h"
#include "HttpUrl.h"

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
		CHttpUrl url(urlString);
		if (url.IsInitialized())
		{
			cout << "HOST: " << url.GetDomain() << endl;
			cout << "PORT: " << url.GetDomain() << endl;
			cout << "DOC: " << url.GetDocument() << endl;
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

