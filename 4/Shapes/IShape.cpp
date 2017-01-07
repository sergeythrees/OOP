#include "stdafx.h"
#include "IShape.h"

IShape::IShape(const std::string & type, std::string outlineColor)
	:m_type(type),
	m_area(0),
	m_perimeter(0), 
	m_outlineColor(outlineColor),
	m_wasChanged(true)
{
}

double IShape::GetArea()
{
	if (m_wasChanged)
		CalculateArea();
	return m_area;
}

double IShape::GetPerimeter()
{
	if (m_wasChanged)
		m_perimeter = CalculatePerimeter();
	return m_perimeter;
}

std::string IShape::GetOutlineColor()
{
	return m_outlineColor;
}

std::string IShape::ToString()
{
	std::ostringstream strm;
	strm << m_type + ": "
		<< "  S: " << GetArea()
		<< "  P: " << GetPerimeter()
		<< "  OutlineColor: " << GetOutlineColor()
		<< UniqueProperties();
	return strm.str();
}