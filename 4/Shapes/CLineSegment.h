#pragma once
#include "IShape.h"
#include "Point.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(Point const& pointA, Point const& pointB, 
		std::string const& outlineColor);
	~CLineSegment() = default;

	Point const& GetPointA() const;
	Point const& GetPointB() const;
	double GetPerimeter() const override;
	
private:
	std::string UniqueProperties() const override;

	Point m_pointA;
	Point m_pointB;
};

std::istream & operator >> (std::istream & stream, std::shared_ptr<CLineSegment> & line);