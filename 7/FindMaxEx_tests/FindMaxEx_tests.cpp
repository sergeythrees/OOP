#include "stdafx.h"
#include <vector>
#include <functional>
#include "../FindMaxEx/FindMaxEx.h"
#include "./res/CAthlete.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(FindMaxEx_function)

	struct NumbersFixture
	{
		std::vector<int> numbers;
		int max = 0;
	};

	BOOST_FIXTURE_TEST_SUITE(when_work_with_vector_of_int_numbers, NumbersFixture)
		BOOST_AUTO_TEST_CASE(should_not_find_if_vector_is_empty)
		{
			BOOST_CHECK(!FindMaxEx(numbers, max, less<int>()));
			BOOST_CHECK_EQUAL(max, 0);
		}
		BOOST_AUTO_TEST_CASE(should_find_if_vector_is_singleton)
		{
			numbers.push_back(10);
			BOOST_CHECK(FindMaxEx(numbers, max, less<int>()));
			BOOST_CHECK_EQUAL(max, 10);
		}
		BOOST_AUTO_TEST_CASE(can_find_max_number)
		{
			numbers.push_back(-3);
			numbers.push_back(-8);
			BOOST_CHECK(FindMaxEx(numbers, max, less<int>()));
			BOOST_CHECK_EQUAL(max, -3);

			numbers.push_back(0);
			numbers.push_back(5);
			BOOST_CHECK(FindMaxEx(numbers, max, less<int>()));
			BOOST_CHECK_EQUAL(max, 5);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct StringFixture
	{
		std::vector<std::string> strings;
		std::string max;
	};

	BOOST_FIXTURE_TEST_SUITE(when_work_with_vector_of_strings, StringFixture)
		BOOST_AUTO_TEST_CASE(should_not_find_if_vector_is_empty)
		{
			BOOST_CHECK(!FindMaxEx(strings, max, less<string>()));
			BOOST_CHECK(max.empty());
		}
		BOOST_AUTO_TEST_CASE(should_find_if_vector_is_singleton)
		{
			strings.push_back("alone");
			BOOST_CHECK(FindMaxEx(strings, max, less<string>()));
			BOOST_CHECK_EQUAL(max, "alone");
		}
		BOOST_AUTO_TEST_CASE(can_find_max_string)
		{
			strings.assign({ "first" , "third" , "second" });
			BOOST_CHECK(FindMaxEx(strings, max, less<string>()));
			BOOST_CHECK_EQUAL(max, "third");
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct AthletesFixture
	{
		std::vector<CAthlete> athletes;
		CAthlete max;
		std::function<bool(CAthlete a, CAthlete b)> lessHeight 
			= [](CAthlete a, CAthlete b) { return a.Height() < b.Height(); };
		std::function<bool(CAthlete a, CAthlete b)> lessWeight
			= [](CAthlete a, CAthlete b) { return a.Weight() < b.Weight(); };
	};

	BOOST_FIXTURE_TEST_SUITE(when_work_with_vector_of_classes, AthletesFixture)
		BOOST_AUTO_TEST_CASE(should_not_find_if_vector_is_empty)
		{
			BOOST_CHECK(!FindMaxEx(athletes, max, lessHeight));
			BOOST_CHECK(max == CAthlete());
		}
		BOOST_AUTO_TEST_CASE(should_find_if_vector_is_singleton)
		{
			athletes.push_back({"Ronaldinho", 181, 80.5 });
			BOOST_CHECK(FindMaxEx(athletes, max, lessHeight));
			BOOST_CHECK_EQUAL(max.Name(), "Ronaldinho");

			BOOST_CHECK(FindMaxEx(athletes, max, lessWeight));
			BOOST_CHECK_EQUAL(max.Name(), "Ronaldinho");
		}
		BOOST_AUTO_TEST_CASE(can_find_class_with_max_optional_value)
		{
			athletes.assign({ 
				{ "Ronaldinho", 181, 80.5 }, 
				{ "Messi", 170, 70 },
				{ "Pele", 173, 71.5 },
				{ "Jonah Hill", 170, 105 }
			});

			BOOST_CHECK(FindMaxEx(athletes, max, lessHeight));
			BOOST_CHECK_EQUAL(max.Name(), "Ronaldinho");

			BOOST_CHECK(FindMaxEx(athletes, max, lessWeight));
			BOOST_CHECK_EQUAL(max.Name(), "Jonah Hill");

		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()