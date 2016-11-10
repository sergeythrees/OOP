#include "stdafx.h"
#include "..\vector\VectorProcessor.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>

#define CHECK_CLOSE_COLLECTION(aa, bb, tolerance) { \
    using std::distance; \
    using std::begin; \
    using std::end; \
    auto a = begin(aa), ae = end(aa); \
    auto b = begin(bb); \
    BOOST_REQUIRE_EQUAL(distance(a, ae), distance(b, end(bb))); \
    for(; a != ae; ++a, ++b) { \
        BOOST_CHECK_CLOSE(*a, *b, tolerance); \
    } \
}

using namespace std;

void VerifyProcessVector(vector<double> resultVector, vector<double> expectedResult)
{
	ProcessVector(resultVector);
	CHECK_CLOSE_COLLECTION(resultVector, expectedResult, 0.1);
}

BOOST_AUTO_TEST_SUITE(ProcessVector_check)


BOOST_AUTO_TEST_CASE(should_makes_empty_vector_from_empty_vector)
{
	VerifyProcessVector({}, {});
}


BOOST_AUTO_TEST_CASE(should_multiple_all_elements_at_min_element)
{
	VerifyProcessVector(	
		{ -1.5689, 0, -25.5689, 33.435, 2, 1 }, 
		{ 40.12, 0, 653.8, -854.9, -51.14, -25.57 }	);
}

BOOST_AUTO_TEST_SUITE_END()
