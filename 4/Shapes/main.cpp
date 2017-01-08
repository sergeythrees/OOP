#include "stdafx.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectarangle.h"
#include "CCirlcle.h"

using namespace std;

int main()
{
	CLineSegment line{ {1,2}, {0,0}, "red" };
	cout << line.ToString() << endl;

	CTriangle triangle( { 1,4 },{ 0,0 },{ -2,-1 }, "red" , "white");
	cout << triangle.ToString() << endl;

	CRectarangle rect({ 1,1 }, { 2,0 }, "red", "white");
	cout << rect.ToString() << endl;

	CCircle circ({ 0,0 }, 5, "blue", "grey");
	cout << circ.ToString() << endl;
	return 0;
}

