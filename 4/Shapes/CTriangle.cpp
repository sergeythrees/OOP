#include "stdafx.h"
#include "GeometricFunctions.h"
#include "CTriangle.h"

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

double CTriangle::CalculateArea() const
{
	double p = CalculatePerimeter() / 2;
	double a = CalculateLineLenght(m_vertexA, m_vertexB);
	double b = CalculateLineLenght(m_vertexA, m_vertexB);
	double c = CalculateLineLenght(m_vertexA, m_vertexB);

	return sqrt(p*(p - a)*(p - b)*(p - c));
}

double CTriangle::CalculatePerimeter() const
{
	double a = CalculateLineLenght(m_vertexA, m_vertexB);
	double b = CalculateLineLenght(m_vertexA, m_vertexB);
	double c = CalculateLineLenght(m_vertexA, m_vertexB);

	return a + b + c;
}

std::string CTriangle::UniqueProperties() const
{
	std::stringstream strm;
	strm << ", Coordinates: {(" << m_vertexA.x
		<< ";" << m_vertexA.y
		<< "),(" << m_vertexB.x
		<< ";" << m_vertexB.y
		<< "),(" << m_vertexC.x
		<< ";" << m_vertexC.y << ")}";
	return ISolidShape::UniqueProperties() + strm.str();
}