#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(const Point & leftTop, const Point & rightBottom, const std::string & outlineColor, const std::string & fillColor)
	:ISolidShape("Rectangle", outlineColor, fillColor)
{
	Point LeftBottom { leftTop.x,  rightBottom.y };
	Point RightTop { rightBottom.x,  leftTop.y };
	m_vertices.assign({ 
		LeftBottom, leftTop , RightTop, rightBottom });
}

const Point & CRectangle::GetLeftTop() const
{
	return m_vertices[1];
}

const Point & CRectangle::GetRightBottom() const
{
	return m_vertices[3];
}

double CRectangle::GetWidth() const
{
	return GetSideLenght(m_vertices[0], m_vertices[1]);
}

double CRectangle::GetHeight() const
{
	return GetSideLenght(m_vertices[1], m_vertices[2]);
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
	return (GetWidth() + GetHeight()) *2;
}

std::string CRectangle::UniqueProperties() const
{
	std::stringstream strm;
	strm << ", W: " << GetWidth()
		<< ", H:" << GetHeight();
	return ISolidShape::UniqueProperties() + strm.str();
}
