#include "stdafx.h"
#include "../Shapes/Point.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/CRectarangle.h"
#include "../Shapes/CCircle.h"

bool  ArePointsEqual(const Point& a, const Point& b)
{
	return (a.x == b.x && a.y == b.y);
}

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
		BOOST_CHECK(ArePointsEqual(shape.GetPointA(), Point{ 0,0 }));
		BOOST_CHECK(ArePointsEqual(shape.GetPointB(), Point{ 2,2 }));
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

struct TriangleFixture
{
	CTriangle shape;
	TriangleFixture()
		:shape({ 0,0 }, { 2,2 }, { 2,0 }, "blue", "white")
	{}

};
BOOST_FIXTURE_TEST_SUITE(CTriangle_, TriangleFixture)

	BOOST_AUTO_TEST_CASE(can_get_perimeter)
	{
		BOOST_CHECK_CLOSE(shape.GetPerimeter(), 6.8284, 0.1);
	}
	BOOST_AUTO_TEST_CASE(can_get_area)
	{
		BOOST_CHECK_CLOSE(shape.GetArea(), 2, 0.1);
	}
	BOOST_AUTO_TEST_CASE(can_get_vertices)
	{
		BOOST_CHECK(ArePointsEqual(shape.GetVertexA(), Point{ 0,0 }));
		BOOST_CHECK(ArePointsEqual(shape.GetVertexB(), Point{ 2,2 }));
		BOOST_CHECK(ArePointsEqual(shape.GetVertexC(), Point{ 2,0 }));
	}
	BOOST_AUTO_TEST_CASE(can_get_outline_color)
	{
		BOOST_CHECK_EQUAL(shape.GetOutlineColor(), "blue");
	}
	BOOST_AUTO_TEST_CASE(can_get_fill_color)
	{
		BOOST_CHECK_EQUAL(shape.GetFillColor(), "white");
	}
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string_correctly)
	{
		BOOST_CHECK_EQUAL(shape.ToString(), 
			"Triangle:   S: 2,  P: 6.82843,  \
OutlineColor: blue, FillColor: white, Vertices: {(0;0),(2;2),(2;0)}");
	}
BOOST_AUTO_TEST_SUITE_END()

struct RectarangleFixture
{
	CRectarangle shape;
	RectarangleFixture()
		:shape({ 0,3 }, { 4,0 }, "green", "white")
	{}

};
BOOST_FIXTURE_TEST_SUITE(CRectarangle_, RectarangleFixture)

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
		BOOST_CHECK(ArePointsEqual(shape.GetLeftTop(), Point{ 0,3 }));
		BOOST_CHECK(ArePointsEqual(shape.GetRightBottom(), Point{ 4,0 }));
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
			"Rectarangle:   S: 12,  P: 14,  OutlineColor: green, \
FillColor: white, W: 3, H:4");
	}
BOOST_AUTO_TEST_SUITE_END()

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
		BOOST_CHECK(ArePointsEqual(shape.GetCenter(), Point{ 0,0 }));
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
BOOST_AUTO_TEST_SUITE_END()