#include "stdafx.h"
#include "Point.h"
#include "CRectangle.h"

using namespace std;

CRectangle::CRectangle(const Point & leftTop, double width, double height, 
	const std::string & outlineColor, const std::string & fillColor)
	:CSolidShape("Rectangle", outlineColor, fillColor),
	m_leftTop(leftTop),
	m_rightBottom({ leftTop.x + width,  leftTop.y - height }),
	m_width(width),
	m_height(height)
{
	if (width < 0 || height < 0)
		throw (out_of_range("Width and height value should be positive"));
}

const Point & CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

const Point & CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return (m_width + m_height) *2;
}

std::string CRectangle::UniqueProperties() const
{
	std::stringstream strm;
	strm << ", W: " << GetWidth()
		<< ", H:" << GetHeight();
	return CSolidShape::UniqueProperties() + strm.str();
}

