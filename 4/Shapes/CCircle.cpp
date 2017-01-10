#include "stdafx.h"
#include "Point.h"
#include "CCircle.h"

using namespace std;

CCircle::CCircle(const Point & center, const double & radius, const std::string & outlineColor, const std::string & fillColor)
	:CSolidShape("Circle", outlineColor, fillColor),
	m_center(center),
	m_radius(radius)
{
	if (radius < 0)
		throw out_of_range("Radius value should be positive");
}

const Point & CCircle::GetCenter() const
{
	return m_center;
}

const double & CCircle::GetRadius() const
{
	return m_radius;
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::UniqueProperties() const
{
	std::stringstream strm;
	strm << ", Center: " << "(" << GetCenter().x
		<< ";" << GetCenter().y << ")"
		<< ", R:" << GetRadius();
	return CSolidShape::UniqueProperties() + strm.str();
}