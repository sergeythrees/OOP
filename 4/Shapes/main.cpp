#include "stdafx.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CShapesController.h"

using namespace std;

int main()try
{
	std::vector<std::shared_ptr<IShape>>  shapes;
	CShapesController control(shapes, cin);

	while (!cin.eof() && !cin.fail()) try
	{
		control.HandleCommand();		
	}
	catch (const exception& ex)
	{
		cerr << ex.what() << endl;
	}

	control.PrintInfo(cout);

	return EXIT_SUCCESS;
}
catch (const exception& ex)
{
	cerr << ex.what() << endl;
	return EXIT_FAILURE;
}