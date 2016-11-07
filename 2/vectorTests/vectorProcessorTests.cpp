#include "stdafx.h"
#include "..\vector\VectorProcessor.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>
using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

BOOST_AUTO_TEST_SUITE(ProcessVector_check)


BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
{
	vector<double> emptyVector;
	ProcessVector(emptyVector);
	BOOST_CHECK(emptyVector.empty());
}


BOOST_AUTO_TEST_CASE(mult_all_elements_at_zero)
{
	vector<double> numbers = { 0, 1, 2, 3 };
	ProcessVector(numbers);
	BOOST_CHECK(VectorsAreEqual(numbers, { 0, 0, 0, 0 }));
}


BOOST_AUTO_TEST_CASE(mult_all_elements_at_negative_value)
{
	vector<double> numbers = { -1, 0, 1, 2, 3 };
	ProcessVector(numbers);
	BOOST_CHECK(VectorsAreEqual(numbers, { 1, 0, -1, -2, -3 }));
}

BOOST_AUTO_TEST_CASE(process_double_numbers)
{
	vector<double> numbers = { -2.00, 5.3435, -25.5689, -3 };
	ProcessVector(numbers);
	BOOST_CHECK(VectorsAreEqual(numbers, { 51.137, -136.627, 653.768, 76.706 }));
}


BOOST_AUTO_TEST_SUITE_END()