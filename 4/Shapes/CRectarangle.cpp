#include "stdafx.h"
#include "CRectarangle.h"

CRectarangle::CRectarangle(const Point & leftTop, const Point & rightBottom, const std::string & outlineColor, const std::string & fillColor)
	:ISolidShape("Rectarangle", outlineColor, fillColor)
{
	Point LeftBottom { leftTop.x,  rightBottom.y };
	Point RightTop { rightBottom.x,  leftTop.y };
	m_vertices.assign({ 
		LeftBottom, leftTop , RightTop, rightBottom });
}

const Point & CRectarangle::GetLeftTop() const
{
	return m_vertices[1];
}

const Point & CRectarangle::GetRightBottom() const
{
	return m_vertices[3];
}

double CRectarangle::GetWidth() const
{
	return GetSideLenght(m_vertices[0], m_vertices[1]);
}

double CRectarangle::GetHeight() const
{
	return GetSideLenght(m_vertices[1], m_vertices[2]);
}

double CRectarangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double CRectarangle::GetPerimeter() const
{
	return (GetWidth() + GetHeight()) *2;
}

std::string CRectarangle::UniqueProperties() const
{
	std::stringstream strm;
	strm << ", W: " << GetWidth()
		<< ", H:" << GetHeight();
	return ISolidShape::UniqueProperties() + strm.str();
}
