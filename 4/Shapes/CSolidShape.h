#pragma once
#include "ISolidShape.h"
#include "CShape.h"

class CSolidShape : public CShape, public ISolidShape
{
public:
	CSolidShape(const std::string & type, const std::string& outlineColor, const std::string & fillColor);
	virtual ~CSolidShape() = default;
	virtual double GetArea() const { return 0; };
	virtual double GetPerimeter() const { return 0; };

	std::string GetFillColor() const;
protected:
	virtual std::string UniqueProperties() const override;
private:
	std::string m_fillColor;
};