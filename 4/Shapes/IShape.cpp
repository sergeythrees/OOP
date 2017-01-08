#include "stdafx.h"
#include "IShape.h"

IShape::IShape(const std::string & type, const std::string& outlineColor)
	:m_type(type),
	m_outlineColor(outlineColor)
{
}

std::string IShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string IShape::ToString() const
{
	std::ostringstream strm;
	strm << m_type + ": "
		<< "  S: " << GetArea()
		<< ",  P: " << GetPerimeter()
		<< ",  OutlineColor: " << GetOutlineColor()
		<< UniqueProperties();
	return strm.str();
}