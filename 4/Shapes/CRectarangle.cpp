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

double CRectarangle::CalculateArea() const
{
	double a = CalculateSideLenght(m_vertices[0], m_vertices[1]);
	double b = CalculateSideLenght(m_vertices[1], m_vertices[2]);

	return a*b;
}

double CRectarangle::CalculatePerimeter() const
{
	double a = CalculateSideLenght(m_vertices[0], m_vertices[1]);
	double b = CalculateSideLenght(m_vertices[1], m_vertices[2]);

	return (a+b)*2;
}

std::string CRectarangle::UniqueProperties() const
{
	std::stringstream strm;
	strm << ", Vertices: {(" << m_vertices[1].x
		<< ";" << m_vertices[1].y
		<< "),(" << m_vertices[3].x
		<< ";" << m_vertices[3].y
		<< ")" << ")}";
	return ISolidShape::UniqueProperties() + strm.str();
}
