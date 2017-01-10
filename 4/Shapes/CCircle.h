#pragma once
#include "CSolidShape.h"

class CCircle : public CSolidShape
{
public:
	CCircle(
		const Point& center,
		const double& radius,
		const std::string& outlineColor,
		const std::string & fillColor);
	~CCircle() = default;

	const Point& GetCenter() const;
	const double& GetRadius() const;
	double GetArea() const override;
	double GetPerimeter() const override;

private:
	std::string UniqueProperties() const override;

	Point m_center;
	double m_radius;
};