#pragma once
#include "IShape.h"

class ISolidShape : public virtual IShape
{
public:
	ISolidShape() = default;
	virtual ~ISolidShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;

	virtual std::string GetFillColor() const = 0;
};
