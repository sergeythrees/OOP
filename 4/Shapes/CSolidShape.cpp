#include "stdafx.h"
#include "CSolidShape.h"

CSolidShape::CSolidShape(const std::string & type, const std::string& outlineColor, const std::string & fillColor)
	:ISolidShape(),
	CShape(type, outlineColor),
	m_fillColor(fillColor)
{
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShape::ToString() const
{
	return ToStringImpl();
}

std::string CSolidShape::GetOutlineColor() const
{
	return GetOutlineColorImpl();
}

std::string CSolidShape::UniqueProperties() const
{
	return ", FillColor: " + m_fillColor;
}
