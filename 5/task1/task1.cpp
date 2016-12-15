// task1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Rational.h"

CRational bbb(const CRational& a)
{
	return a;
}
int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	CRational r = bbb(5);
	return 0;
}

