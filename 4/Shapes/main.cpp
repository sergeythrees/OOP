#include "stdafx.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CShapesController.h"

using namespace std;

int main()
{
	std::vector<std::shared_ptr<IShape>>  shapes;
	CShapesController control(shapes);
	while (!cin.eof() && !cin.fail())
	{
		string commandLine;
		getline(cin, commandLine);
		control.HandleCommand(commandLine);
	}
	control.PrintInfo(cout);
	return 0;
}