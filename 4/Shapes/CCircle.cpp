#include "stdafx.h"
#include "CCircle.h"

using namespace std;

CCircle::CCircle(const Point & center, const double & radius, const std::string & outlineColor, const std::string & fillColor)
	:ISolidShape("Circle", outlineColor, fillColor),
	m_center(center),
	m_radius(radius)
{
	if (radius < 0)
		throw out_of_range("Radius value should be positive");
}

const Point & CCircle::GetCenter() const
{
	return m_center;
}

const double & CCircle::GetRadius() const
{
	return m_radius;
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::UniqueProperties() const
{
	std::stringstream strm;
	strm << ", Center: " << "(" << GetCenter().x
		<< ";" << GetCenter().y << ")"
		<< ", R:" << GetRadius();
	return ISolidShape::UniqueProperties() + strm.str();
}

std::istream & operator >> (std::istream & stream, std::shared_ptr<CCircle> & circle)
{
	double Ax;
	double Ay;
	double radius;
	std::string outlineColor;
	string fillColor;
	if (
		stream >> Ax &&
		stream >> Ay &&
		stream >> radius &&
		stream >> outlineColor&&
		stream >> fillColor)
	{
		circle = make_shared<CCircle>(CCircle({ Ax, Ay }, radius, outlineColor, fillColor));
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
		stringstream mess;
		mess << "Invalid arguments." << endl
			<< "Use: <Ox> <Oy> <radius> <outlineColor> <fillColor>" << endl;
		throw(invalid_argument(mess.str()));
	}

	return stream;
}