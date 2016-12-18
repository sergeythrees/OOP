#include "stdafx.h"
#include <vector>
#include <functional>
#include "../FindMaxEx/FindMaxEx.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(FindMaxEx_function)

	struct NumbersFixture
	{
		std::vector<int> numbers;
		int maxNumber = 0;
	};

	BOOST_FIXTURE_TEST_SUITE(when_work_with_vector_of_int, NumbersFixture)

		BOOST_AUTO_TEST_CASE(should_not_find_if_vector_is_empty)
		{
			BOOST_CHECK(!FindMaxEx(numbers, maxNumber, isless<int, int>));
		}
		BOOST_AUTO_TEST_CASE(should_find_if_vector_is_singleton)
		{
			numbers.push_back(10);
			BOOST_CHECK(FindMaxEx(numbers, maxNumber, isless<int, int>));
			BOOST_CHECK_EQUAL(maxNumber, 10);
		}
		BOOST_AUTO_TEST_CASE(can_find_max_number)
		{
			numbers.push_back(-3);
			numbers.push_back(-8);
			BOOST_CHECK(FindMaxEx(numbers, maxNumber, isless<int, int>));
			BOOST_CHECK_EQUAL(maxNumber, -3);

			numbers.push_back(0);
			numbers.push_back(5);
			BOOST_CHECK(FindMaxEx(numbers, maxNumber, isless<int, int>));
			BOOST_CHECK_EQUAL(maxNumber, 5);
		}
	BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()