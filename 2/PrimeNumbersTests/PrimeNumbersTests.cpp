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
	BOOST_AUTO_TEST_CASE(makes_empty_set_if_upper_bound_is_less_than_minimal_prime_number)
	{
		BOOST_CHECK(GeneratePrimeNumbersSet(1).empty());
	}
	BOOST_AUTO_TEST_CASE(makes_prime_numbers_set_if_upper_bound_is_not_out_of_range)
    {
		BOOST_CHECK_EQUAL(GeneratePrimeNumbersSet(7).size(), 4);
        BOOST_CHECK_EQUAL(GeneratePrimeNumbersSet(25).size(), 9);
    }

BOOST_AUTO_TEST_SUITE_END()