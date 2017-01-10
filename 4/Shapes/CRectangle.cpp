#include "stdafx.h"
#include "CRectangle.h"

using namespace std;

CRectangle::CRectangle(const Point & leftTop, double width, double height, 
	const std::string & outlineColor, const std::string & fillColor)
	:ISolidShape("Rectangle", outlineColor, fillColor),
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
	return ISolidShape::UniqueProperties() + strm.str();
}

std::istream & operator >> (std::istream & stream, std::shared_ptr<CRectangle> & rectangle)
{
	double Ax;
	double Ay;
	double width;
	double height;
	string outlineColor;
	string fillColor;
	if (
		stream >> Ax &&
		stream >> Ay &&
		stream >> width &&
		stream >> height &&
		stream >> outlineColor&&
		stream >> fillColor)
	{
		rectangle = make_shared<CRectangle>(CRectangle({ Ax,Ay }, width, height, outlineColor, fillColor));
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
		stringstream mess;
		mess << "Invalid arguments." << endl
			<< "Use: <LeftBottom.x> <LeftBottom.y> <width> <height> <outlineColor> <fillColor>" << endl;
		throw(invalid_argument(mess.str()));
	}

	return stream;
}