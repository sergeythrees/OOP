#include "stdafx.h"
#include "PrimeNumbers.h"

const unsigned ARG_COUNT = 2;

using namespace std;

bool IsValidArgumentsCount(int argc)
{
	return (argc == ARG_COUNT);
}

int main(int argc, char * argv[])
{
	int upperBound = 0;
	if (!IsValidArgumentsCount(argc))
	{
		cout << "Неверные аргументы коммандной строки. Используйте :" << endl;
		cout << "PrimeNumbersSetGenerator.exe <upperBound>" << endl;
		cout << "Введите значение upperBound или пустую строку для завершения" << endl;
		if (!(cin >> upperBound))
			return EXIT_SUCCESS;
	}
	else
	{
		upperBound = atoi(argv[1]);
	}





	return EXIT_SUCCESS;
}
