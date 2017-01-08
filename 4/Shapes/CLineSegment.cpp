#include "stdafx.h"
#include "IShape.h"
#include "CLineSegment.h"

CLineSegment::CLineSegment(Point const & pointA, Point const & pointB, std::string const & outlineColor)
	:IShape("Line", outlineColor),
	m_pointA(pointA),
	m_pointB(pointB)
{
}

Point const& CLineSegment::GetPointA() const
{
	return m_pointA;
}

Point const& CLineSegment::GetPointB() const
{
	return m_pointB;
}

double CLineSegment::GetPerimeter() const
{
	return std::hypot(
		m_pointA.x - m_pointB.x,
		m_pointA.y - m_pointB.y);
}

std::string CLineSegment::UniqueProperties() const
{
	std::stringstream strm;
	strm << ", Coordinates: {(" << m_pointA.x
		<< ";" << m_pointA.y 
		<< "),(" << m_pointB.x 
		<< ";" << m_pointB.y << ")}";

	return strm.str();
}
;