#include "stdafx.h"
#include "ISolidShape.h"

ISolidShape::ISolidShape(const std::string & type, std::string outlineColor, const std::string & fillColor)
	:IShape(type, outlineColor),
	m_fillColor(fillColor)
{
}

std::string ISolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string ISolidShape::UniqueProperties() const
{
	return ", FillColor: " + m_fillColor;
}
