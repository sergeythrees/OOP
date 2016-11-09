#include "stdafx.h"
#include "..\vector\VectorProcessor.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace std;

bool VerifyProcessVector(vector<double> input, vector<double> expectedresult)
{
	ProcessVector(input);
	return expectedresult == input;
}

BOOST_AUTO_TEST_SUITE(ProcessVector_check)


BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
{
	vector<double> emptyVector;
	BOOST_CHECK(VerifyProcessVector(emptyVector, emptyVector));
}


BOOST_AUTO_TEST_CASE(multiple_all_elements_at_min_element)
{
	BOOST_CHECK_CLOSE(VerifyProcessVector(
		{ -1.5689, 0, -25.5689, 33.435, 2, 1 }, 
		{ 40.12, 0, 653.8, -854.9, -51.14, -25.57 }), 4);
}

BOOST_AUTO_TEST_SUITE_END()
