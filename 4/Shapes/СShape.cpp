#pragma once
#include "stdafx.h"
#include "CShape.h"

CShape::CShape(const std::string & type, const std::string& outlineColor)
	:IShape(),
	m_type(type),
	m_outlineColor(outlineColor)
{
}

std::string CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CShape::ToString() const
{
	std::ostringstream strm;
	strm << m_type + ": "
		<< "  S: " << GetArea()
		<< ",  P: " << GetPerimeter()
		<< ",  OutlineColor: " << GetOutlineColor()
		<< UniqueProperties();
	return strm.str();
}