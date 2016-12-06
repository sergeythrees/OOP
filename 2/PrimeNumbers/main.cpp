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
	setlocale(LC_ALL, "rus");
	int upperBound = 0;
	if (!IsValidArgumentsCount(argc))
	{
		cout << "Неверные аргументы коммандной строки. Используйте :" << endl;
		cout << "PrimeNumbersSetGenerator.exe <upperBound>" << endl;
		cout << "Введите значение верхней границы поиска или пустую строку для завершения" << endl;
		if (!(cin >> upperBound))
			return EXIT_SUCCESS;
	}
	else
	{
		upperBound = atoi(argv[1]);
	}

	if (!IsValidUpperBound(upperBound))
	{
		cout << "Верхняя граница должна быть в диапазоне от 1 до 10000000" << endl;
		return EXIT_FAILURE;
	}

	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);

	std::copy(primeNumbers.begin(), primeNumbers.end(), std::ostream_iterator<int>(std::cout, " "));


	return EXIT_SUCCESS;
}
