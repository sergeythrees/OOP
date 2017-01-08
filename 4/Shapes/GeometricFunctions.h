#pragma once
#include "Point.h"

double GetLineLenght(const Point & A, const Point & B) 
{
	return hypot(
		A.x - B.x,
		A.y - B.y);
}
