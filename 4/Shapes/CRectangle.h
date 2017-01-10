#pragma once
#include "ISolidShape.h"
#include "Point.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(
		const Point& leftTop,
		double width,
		double height,
		const std::string& outlineColor,
		const std::string & fillColor);
	~CRectangle() = default;

	const Point& GetLeftTop() const;
	const Point& GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	double GetArea() const override;
	double GetPerimeter() const override;
private:
	std::string UniqueProperties() const override;
	
	Point m_leftTop;
	Point m_rightBottom;
	double m_width;
	double m_height;
};


std::istream & operator >> (std::istream & stream, std::shared_ptr<CRectangle> & rectangle);