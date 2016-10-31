#include "stdafx.h"
#include "..\vector\VectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

BOOST_AUTO_TEST_SUITE(ProcessVector_function)


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

BOOST_AUTO_TEST_SUITE_END()