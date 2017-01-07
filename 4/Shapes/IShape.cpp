#include "stdafx.h"
#include "IShape.h"

IShape::IShape(const std::string & type, std::string outlineColor)
	:m_type(type),
	m_area(0),
	m_perimeter(0), 
	m_outlineColor(outlineColor),
	m_wasAreaCalculated(false),
	m_wasPerimeterCalculated(false)
{
}

double IShape::GetArea()
{
	if (!m_wasAreaCalculated)
	{
		m_area = CalculateArea();
		m_wasAreaCalculated = true;
	}

	return m_area;
}

double IShape::GetPerimeter()
{
	if (!m_wasPerimeterCalculated)
	{
		m_perimeter = CalculatePerimeter();
		m_wasPerimeterCalculated = true;
	}
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
		<< ",  P: " << GetPerimeter()
		<< ",  OutlineColor: " << GetOutlineColor()
		<< UniqueProperties();
	return strm.str();
}