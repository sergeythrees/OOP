#include "stdafx.h"
#include "IShape.h"
#include "CLineSegment.h"

CLineSegment::CLineSegment(Point const & startPoint, Point const & endPoint, std::string const & outlineColor)
	:IShape("Line", outlineColor),
	m_startPoint(startPoint),
	m_endPoint(endPoint)
{
}

Point const& CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

Point const& CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}

double CLineSegment::CalculateArea() const
{
	return 0;
}

double CLineSegment::CalculatePerimeter() const
{
	return std::hypot(
		m_startPoint.x - m_endPoint.x, 
		m_startPoint.y - m_endPoint.y);
};

std::string  CLineSegment::UniqueProperties() const
{
	return std::string();
}