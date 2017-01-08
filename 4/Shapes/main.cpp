#include "stdafx.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectarangle.h"
#include "CCircle.h"

using namespace std;

int main()
{
	CLineSegment line({ 0,0 }, { 2,2 }, "red");
	cout << line.ToString() << endl;

	CTriangle triangle({ 0,0 }, { 2,2 }, { 2,0 }, "blue", "white");
	cout << triangle.ToString() << endl;

	CRectarangle rect({ 0,3 }, { 4,0 }, "green", "white");
	cout << rect.ToString() << endl;

	CCircle circ({ 0,0 }, 5, "grey", "white");
	cout << circ.ToString() << endl;
	return 0;
}

