#pragma once
#include "Point.h"
#include "CShape.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(Point const& pointA, Point const& pointB, 
		std::string const& outlineColor);
	~CLineSegment() = default;

	Point const& GetPointA() const;
	Point const& GetPointB() const;
	double GetPerimeter() const override;
	virtual std::string ToString() const final;
	virtual std::string GetOutlineColor() const final;
	
private:
	std::string UniqueProperties() const override;

	Point m_pointA;
	Point m_pointB;
};