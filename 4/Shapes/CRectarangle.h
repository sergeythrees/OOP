#pragma once
#include "ISolidShape.h"
#include "Point.h"

class CRectarangle : public ISolidShape
{
public:
	CRectarangle(
		const Point& leftTop,
		const Point& rightBottom,
		const std::string& outlineColor,
		const std::string & fillColor);

	const Point& GetLeftTop() const;
	const Point& GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	double GetArea() const override;
	double GetPerimeter() const override;
private:
	std::string UniqueProperties() const override;

	double GetSideLenght(const Point & A1, const Point & B1) const
	{
		return hypot(
			A1.x - B1.x,
			A1.y - B1.y);
	}

	Vertices m_vertices;
};

