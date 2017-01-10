#include "stdafx.h"

using namespace std;

struct CircleFixture
{
	CCircle shape;
	CircleFixture()
		:shape({ 0,0 }, 5, "grey", "white")
	{}
};
BOOST_FIXTURE_TEST_SUITE(CCircle_, CircleFixture)

	BOOST_AUTO_TEST_CASE(can_get_perimeter)
	{
		BOOST_CHECK_CLOSE(shape.GetPerimeter(), 31.4159, 0.1);
	}
	BOOST_AUTO_TEST_CASE(can_get_area)
	{
		BOOST_CHECK_CLOSE(shape.GetArea(), 78.5398, 0.1);
	}
	BOOST_AUTO_TEST_CASE(can_get_center_and_radius)
	{
		ArePointsEqual(shape.GetCenter(), Point{ 0,0 });
		BOOST_CHECK_CLOSE(shape.GetRadius(), 5, 0.1);
	}
	BOOST_AUTO_TEST_CASE(can_get_outline_color)
	{
		BOOST_CHECK_EQUAL(shape.GetOutlineColor(), "grey");
	}
	BOOST_AUTO_TEST_CASE(can_get_fill_color)
	{
		BOOST_CHECK_EQUAL(shape.GetFillColor(), "white");
	}
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string_correctly)
	{
		BOOST_CHECK_EQUAL(shape.ToString(),
			"Circle:   S: 78.5398,  P: 31.4159,  OutlineColor: grey, \
FillColor: white, Center: (0;0), R:5");
	}
	BOOST_AUTO_TEST_CASE(should_throw_appropriate_exception_when_radius_value_is_not_positive)
	{
		VerifyException<std::out_of_range>(
			[]() {CCircle(Point{ 0,0 }, -1, "red", "red"); },
			"Radius value should be positive");
	}
BOOST_AUTO_TEST_SUITE_END()