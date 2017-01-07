#pragma once
#include "Point.h"

double CalculateLineLenght(const Point & A, const Point & B) 
{
	return hypot(
		A.x - B.x,
		A.y - B.y);
}
