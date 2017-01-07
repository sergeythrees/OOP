#pragma once
#include "stdafx.h"

enum ShapeTypes
{
	LINE,
	TRIANGLE,
	RECTARANGLE,
	CIRCLE
};

std::map<ShapeTypes, std::string> shapeToStringMap
{
	{ LINE, "Line" },
	{ TRIANGLE, "Triangle" },
	{ RECTARANGLE, "Rectarangle" },
	{ CIRCLE, "Circle" }
};

std::string ShapeToString(ShapeTypes shape)
{
	return shapeToStringMap.at(shape);
}