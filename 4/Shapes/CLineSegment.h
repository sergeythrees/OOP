#pragma once
#include "IShape.h"
#include "Point.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(Point const& pointA, Point const& pointB, std::string const& outlineColor);

	Point const& GetPointA() const;
	Point const& GetPointB() const;
	
private:
	double CalculatePerimeter() const override;
	std::string UniqueProperties() const override;

	Point m_pointA;
	Point m_pointB;
};