#include "stdafx.h"
#include "GeometricFunctions.h"
#include "CTriangle.h"

using namespace std;

CTriangle::CTriangle(const Point & vertexA, const Point & vertexB, const Point & vertexC, const std::string & outlineColor, const std::string & fillColor)
	:ISolidShape("Triangle", outlineColor, fillColor),
	m_vertexA(vertexA),
	m_vertexB(vertexB),
	m_vertexC(vertexC)
{
}

const Point & CTriangle::GetVertexA() const
{
	return m_vertexA;
}

const Point & CTriangle::GetVertexB() const
{
	return m_vertexB;
}

const Point & CTriangle::GetVertexC() const
{
	return m_vertexC;
}

double CTriangle::GetArea() const
{
	double p = GetPerimeter() / 2;
	double a = GetLineLenght(m_vertexA, m_vertexB);
	double b = GetLineLenght(m_vertexB, m_vertexC);
	double c = GetLineLenght(m_vertexC, m_vertexA);

	return sqrt(p*(p - a)*(p - b)*(p - c));
}

double CTriangle::GetPerimeter() const
{
	double a = GetLineLenght(m_vertexA, m_vertexB);
	double b = GetLineLenght(m_vertexB, m_vertexC);
	double c = GetLineLenght(m_vertexC, m_vertexA);

	return a + b + c;
}

std::string CTriangle::UniqueProperties() const
{
	std::stringstream strm;
	strm << ", Vertices: {(" << m_vertexA.x
		<< ";" << m_vertexA.y
		<< "),(" << m_vertexB.x
		<< ";" << m_vertexB.y
		<< "),(" << m_vertexC.x
		<< ";" << m_vertexC.y << ")}";
	return ISolidShape::UniqueProperties() + strm.str();
}

std::istream & operator >> (std::istream & stream, std::shared_ptr<CTriangle> & triangle)
{
	double Ax;
	double Ay;
	double Bx;
	double By;
	double Cx;
	double Cy;

	string outlineColor;
	string fillColor;
	if (
		stream >> Ax &&
		stream >> Ay &&
		stream >> Bx &&
		stream >> By &&
		stream >> Cx &&
		stream >> Cy &&
		stream >> outlineColor&&
		stream >> fillColor)
	{
		triangle = make_shared<CTriangle>(CTriangle({ Ax,Ay }, { Bx, By }, { Cx, Cy }, outlineColor, fillColor));
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
		stringstream mess;
		mess << "Invalid arguments." << endl
			<< "Use: <Ax> <Ay> <Bx> <By> <Cx> <Cy> <outlineColor> <fillColor>" << endl;
		throw(invalid_argument(mess.str()));
	}

	return stream;
}