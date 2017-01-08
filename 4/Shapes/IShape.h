#pragma once

class IShape
{
public:
	IShape(const std::string & type, std::string outlineColor);
	virtual double GetArea() const { return 0; };
	virtual double GetPerimeter() const { return 0; };
	virtual std::string GetOutlineColor() const;

	std::string ToString();
protected:
	virtual std::string UniqueProperties() const { return ""; };

private:
	std::string m_type;
	std::string m_outlineColor;
};
