#include "stdafx.h"
#include "IShape.h"
#include "CLineSegment.h"

using namespace std;

CLineSegment::CLineSegment(Point const & pointA, Point const & pointB, std::string const & outlineColor)
	:IShape("Line", outlineColor),
	m_pointA(pointA),
	m_pointB(pointB)
{
}

Point const& CLineSegment::GetPointA() const
{
	return m_pointA;
}

Point const& CLineSegment::GetPointB() const
{
	return m_pointB;
}

double CLineSegment::GetPerimeter() const
{
	return std::hypot(
		m_pointA.x - m_pointB.x,
		m_pointA.y - m_pointB.y);
}

std::string CLineSegment::UniqueProperties() const
{
	std::stringstream strm;
	strm << ", Coordinates: {(" << m_pointA.x
		<< ";" << m_pointA.y 
		<< "),(" << m_pointB.x 
		<< ";" << m_pointB.y << ")}";

	return strm.str();
}

std::istream & operator >> (std::istream & stream, shared_ptr<CLineSegment> & line)
{
	double Ax;
	double Ay;
	double Bx;
	double By;
	std::string outlineColor;
	if (
		stream >> Ax &&
		stream >> Ay &&
		stream >> Bx &&
		stream >> By &&
		stream >> outlineColor)
	{
		line = make_shared<CLineSegment>(CLineSegment({ Ax,Ay }, { Bx, By }, outlineColor));
	}
	else
	{

		stream.setstate(std::ios_base::failbit);
		stringstream mess;
		mess << "Invalid arguments." << endl
			<< "Use: <Ax> <Ay> <Bx> <By> <outlineColor>" << endl;
		throw(invalid_argument(mess.str()));
	}

	return stream;
}