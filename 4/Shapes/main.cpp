#include "stdafx.h"
#include "CLineSegment.h"

using namespace std;

int main()
{
	CLineSegment line{ {1,2}, {0,0}, "red" };
	cout << line.ToString() << endl;
	return 0;
}

