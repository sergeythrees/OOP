#include "stdafx.h"

using namespace std;

struct RectangleFixture
{
	CRectangle shape;
	RectangleFixture()
		:shape({ 0,3 }, 3, 4, "green", "white")
	{}

};
BOOST_FIXTURE_TEST_SUITE(CRectangle_, RectangleFixture)

	BOOST_AUTO_TEST_CASE(can_get_perimeter)
	{
		BOOST_CHECK_CLOSE(shape.GetPerimeter(), 14, 0.1);
	}
	BOOST_AUTO_TEST_CASE(can_get_area)
	{
		BOOST_CHECK_CLOSE(shape.GetArea(), 12, 0.1);
	}
	BOOST_AUTO_TEST_CASE(can_get_vertices)
	{
		ArePointsEqual(shape.GetLeftTop(), Point{ 0,3 });
		ArePointsEqual(shape.GetRightBottom(), Point{ 3,-1 });
	}
	BOOST_AUTO_TEST_CASE(can_get_height_and_width)
	{
		BOOST_CHECK_CLOSE(shape.GetHeight(), 4, 0.1);
		BOOST_CHECK_CLOSE(shape.GetWidth(), 3, 0.1);
	}
	BOOST_AUTO_TEST_CASE(can_get_outline_color)
	{
		BOOST_CHECK_EQUAL(shape.GetOutlineColor(), "green");
	}
	BOOST_AUTO_TEST_CASE(can_get_fill_color)
	{
		BOOST_CHECK_EQUAL(shape.GetFillColor(), "white");
	}
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string_correctly)
	{
		BOOST_CHECK_EQUAL(shape.ToString(),
			"Rectangle:   S: 12,  P: 14,  OutlineColor: green, \
FillColor: white, W: 3, H:4");
	}
	BOOST_AUTO_TEST_CASE(should_throw_appropriate_exception_when_width_or_height_value_is_not_positive)
	{
		VerifyException<std::out_of_range>(
			[]() {CRectangle(Point{ 0,0 }, -1, 1, "red", "red"); },
			"Width and height value should be positive");

		VerifyException<std::out_of_range>(
			[]() {CRectangle(Point{ 0,0 }, 1, -1, "red", "red"); },
			"Width and height value should be positive");
	}
BOOST_AUTO_TEST_SUITE_END()