#include "stdafx.h"
#include "../PrimeNumbers/PrimeNumbers.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)

	BOOST_AUTO_TEST_CASE(makes_empty_set_if_upper_bound_is_out_of_range)
	{
		BOOST_CHECK(GeneratePrimeNumbersSet(-1).empty());
		BOOST_CHECK(GeneratePrimeNumbersSet(0).empty());
		BOOST_CHECK(GeneratePrimeNumbersSet(100000001).empty());
	}

BOOST_AUTO_TEST_SUITE_END()