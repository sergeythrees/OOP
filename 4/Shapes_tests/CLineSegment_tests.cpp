#include "stdafx.h"

using namespace std;

struct LineFixture
{
	CLineSegment shape;
	LineFixture()
		:shape( { 0,0 }, { 2,2 }, "red" )
	{}
	
};
BOOST_FIXTURE_TEST_SUITE(CLineSegment_, LineFixture)

	BOOST_AUTO_TEST_CASE(can_get_perimeter)
	{
		BOOST_CHECK_CLOSE(shape.GetPerimeter(), sqrt(8), 0.1);
	}
	BOOST_AUTO_TEST_CASE(area_is_zero_always)
	{
		BOOST_CHECK(shape.GetArea() == 0);
	}
	BOOST_AUTO_TEST_CASE(can_get_endpoints)
	{
		ArePointsEqual(shape.GetPointA(), Point{ 0,0 });
		ArePointsEqual(shape.GetPointB(), Point{ 2,2 });
	}
	BOOST_AUTO_TEST_CASE(can_get_outline_color)
	{
		BOOST_CHECK_EQUAL(shape.GetOutlineColor(), "red");
	}
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string_correctly)
	{
		BOOST_CHECK_EQUAL(shape.ToString(), "Line:   S: 0,  P: 2.82843,  OutlineColor: red, Coordinates: {(0;0),(2;2)}");
	}
BOOST_AUTO_TEST_SUITE_END()
