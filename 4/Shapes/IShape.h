#pragma once

class IShape
{
public:
	IShape(const std::string & type, std::string outlineColor);
	double GetArea();
	double GetPerimeter();
	virtual std::string GetOutlineColor();

	std::string ToString();
protected:
	virtual double CalculateArea() const = 0;
	virtual double CalculatePerimeter() const = 0;
	virtual std::string UniqueProperties() const = 0;

private:
	std::string m_type;
	double m_area;
	double m_perimeter;
	std::string m_outlineColor;
	bool m_wasChanged;
};
