#include "stdafx.h"
#include "PrimeNumbers.h"

using namespace std;

void InitSieve(int upperBound, vector<bool>& sieve)
{
	sieve[0] = sieve[1] = false;
	int sqrtUpperBound = static_cast<int>(round(sqrt(upperBound)));
	for (int i = MIN_PRIME_NUMBER; i <= sqrtUpperBound; ++i)
	{
		if (sieve[i])
		{
			int speed = (i == 2) ? i : i + i;
			for (int j = i * i; j <= upperBound; j += speed)
			{
				sieve[j] = false;
			}
		}
	}
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	set<int> result;
	if (IsValidUpperBound(upperBound) && upperBound >= MIN_PRIME_NUMBER)
	{
		vector<bool> sieve(upperBound + 1, true);
		InitSieve(upperBound, sieve);
		for (int i = MIN_PRIME_NUMBER; i <= upperBound; ++i)
		{
			if (sieve[i])
			{
				result.emplace_hint(result.end(), i);
			}
		}
	}
	return result;
}

bool IsValidUpperBound(int upperBound)
{
	return (upperBound > 0 && upperBound <= MAX_UPPER_BOUND);
}
