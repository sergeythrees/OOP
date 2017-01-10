#include "stdafx.h"

using namespace std;

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
		ArePointsEqual(shape.GetVertexA(), Point{ 0,0 });
		ArePointsEqual(shape.GetVertexB(), Point{ 2,2 });
		ArePointsEqual(shape.GetVertexC(), Point{ 2,0 });
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
