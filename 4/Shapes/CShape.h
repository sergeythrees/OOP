#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape(const std::string & type, const std::string& outlineColor);
	virtual ~CShape() = default;

	virtual double GetArea() const { return 0; };
	virtual double GetPerimeter() const { return 0; };

	std::string ToString() const final;
protected:
	std::string GetOutlineColorImpl() const;
	virtual std::string UniqueProperties() const { return ""; };

private:
	std::string m_type;
	std::string m_outlineColor;
};