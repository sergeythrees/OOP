#include "stdafx.h"
#include "ParseUrl.h"

const unsigned ARG_COUNT = 2;

using namespace std;

bool IsValidArgumentsCount(int argc)
{
	return (argc == ARG_COUNT);
}

int main(int argc, char * argv[])
{
	setlocale(LC_ALL, "rus");
	string urlString;
	if (!IsValidArgumentsCount(argc))
	{
		cout << "Неверные аргументы коммандной строки. Используйте :" << endl;
		cout << "ParseUrl.exe <URL line>" << endl;
		cout << "Введите URL или пустую строку для завершения" << endl;
		cin >> urlString;
		if (urlString.empty())
			return EXIT_SUCCESS;
	}
	else
	{
		urlString = argv[1];
	}

	return EXIT_SUCCESS;
}
