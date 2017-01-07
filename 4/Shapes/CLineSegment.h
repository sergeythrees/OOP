#pragma once
#include "IShape.h"
#include "Point.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(Point const& startPoint, Point const& endPoint, std::string const& outlineColor);

	Point const& GetStartPoint() const;
	Point const& GetEndPoint() const;
protected:
	virtual double CalculateArea() const override;
	virtual double CalculatePerimeter() const override;
	std::string UniqueProperties() const override;
private:
	Point m_startPoint;
	Point m_endPoint;
};