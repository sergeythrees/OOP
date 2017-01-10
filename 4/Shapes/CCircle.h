#pragma once
#include "ISolidShape.h"
#include "Point.h"

class CCircle : public ISolidShape
{
public:
	CCircle(
		const Point& center,
		const double& radius,
		const std::string& outlineColor,
		const std::string & fillColor);

	const Point& GetCenter() const;
	const double& GetRadius() const;
	double GetArea() const override;
	double GetPerimeter() const override;

private:
	std::string UniqueProperties() const override;

	Point m_center;
	double m_radius;
};


std::istream & operator >> (std::istream & stream, std::shared_ptr<CCircle> & circle);