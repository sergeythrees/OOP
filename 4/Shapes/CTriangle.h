#pragma once
#include "ISolidShape.h"
#include "Point.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(
		const Point& vertexA, 
		const Point& vertexB, 
		const Point& vertexC, 
		const std::string& outlineColor, 
		const std::string & fillColor);
	~CTriangle() = default;

	const Point& GetVertexA() const;
	const Point& GetVertexB() const;
	const Point& GetVertexC() const;
	double GetArea() const override;
	double GetPerimeter() const override;

private:
	std::string UniqueProperties() const override;

	Point m_vertexA;
	Point m_vertexB;
	Point m_vertexC;
};

std::istream & operator >> (std::istream & stream, std::shared_ptr<CTriangle> & triangle);