#pragma once
#include "stdafx.h"

namespace
{
	void  ArePointsEqual(const Point& a, const Point& b)
	{
		BOOST_CHECK_CLOSE(a.x, b.x, 0.1);
		BOOST_CHECK_CLOSE(a.y, b.y, 0.1);
	}

	void VerifyLine(const CLineSegment& line,
		const Point& a, const Point& b, const std::string outlineColor)
	{
		ArePointsEqual(line.GetPointA(), a);
		ArePointsEqual(line.GetPointB(), b);
		BOOST_CHECK_EQUAL(line.GetOutlineColor(), outlineColor);
	}

	void VerifyTriangle(const CTriangle& triangle,
		const Point& a, const Point& b, const Point& c, 
		const std::string outlineColor, const std::string fillColor)
	{
		ArePointsEqual(triangle.GetVertexA(), a);
		ArePointsEqual(triangle.GetVertexB(), b);
		ArePointsEqual(triangle.GetVertexC(), c);
		BOOST_CHECK_EQUAL(triangle.GetOutlineColor(), outlineColor);
		BOOST_CHECK_EQUAL(triangle.GetFillColor(), fillColor);
	}

	void VerifyRectangle(const CRectangle& rectangle,
		const Point& leftTop, double width, double height,
		const std::string outlineColor, const std::string fillColor)
	{
		ArePointsEqual(rectangle.GetLeftTop(), leftTop);
		BOOST_CHECK_CLOSE(rectangle.GetWidth(), width, 0.1);
		BOOST_CHECK_CLOSE(rectangle.GetHeight(), height, 0.1);
		BOOST_CHECK_EQUAL(rectangle.GetOutlineColor(), outlineColor);
		BOOST_CHECK_EQUAL(rectangle.GetFillColor(), fillColor);
	}

	void VerifyCircle(const CCircle& circle,
		const Point& center, double radius,
		const std::string outlineColor, const std::string fillColor)
	{
		ArePointsEqual(circle.GetCenter(), center);
		BOOST_CHECK_CLOSE(circle.GetRadius(), radius, 0.1);
		BOOST_CHECK_EQUAL(circle.GetOutlineColor(), outlineColor);
		BOOST_CHECK_EQUAL(circle.GetFillColor(), fillColor);
	}

	template <typename Ex, typename Fn>
	void VerifyException(Fn && fn, const std::string & expectedDescription)
	{
		BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
			BOOST_CHECK_EQUAL(e.what(), expectedDescription);
			return e.what() == expectedDescription;
		});
	}
}