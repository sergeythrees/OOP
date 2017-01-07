#pragma once
#include "IShape.h"
#include "Point.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(Point const& startPoint, Point const& endPoint, std::string const& outlineColor);

	Point const& GetStartPoint() const;
	Point const& GetEndPoint() const;
	
private:
	virtual double CalculatePerimeter() const override;

	Point m_startPoint;
	Point m_endPoint;
};