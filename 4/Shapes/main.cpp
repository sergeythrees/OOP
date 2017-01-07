#include "stdafx.h"
#include "CLineSegment.h"
#include "CTriangle.h"

using namespace std;

int main()
{
	CLineSegment line{ {1,2}, {0,0}, "red" };
	cout << line.ToString() << endl;

	CTriangle triangle( { 1,4 },{ 0,0 },{ -2,-1 }, "red" , "white");
	cout << triangle.ToString() << endl;
	return 0;
}

