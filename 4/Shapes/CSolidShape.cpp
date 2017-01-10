#include "stdafx.h"
#include "CSolidShape.h"

CSolidShape::CSolidShape(const std::string & type, const std::string& outlineColor, const std::string & fillColor)
	:CShape(type, outlineColor),
	m_fillColor(fillColor)
{
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShape::UniqueProperties() const
{
	return ", FillColor: " + m_fillColor;
}
