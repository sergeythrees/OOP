#pragma once
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	ISolidShape(const std::string & type, std::string outlineColor, const std::string & fillColor);
	std::string GetFillColor() const;
protected:
	virtual std::string UniqueProperties() const override;
private:
	std::string m_fillColor;
};