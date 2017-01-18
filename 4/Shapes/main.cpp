#include "stdafx.h"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CShapesController.h"

using namespace std;

void WorkWithShapesFromStream(istream& input);

int main()try
{
	WorkWithShapesFromStream(cin);

	return EXIT_SUCCESS;
}
catch (const exception& ex)
{
	cerr << ex.what() << endl;
	return EXIT_FAILURE;
}

void WorkWithShapesFromStream(istream& input)
{
	std::vector<std::shared_ptr<CShape>>  shapes;
	CShapesController control(shapes, input);

	cout << "Input shapes or Ctrl+Z for finish" << endl;

	while (!input.eof() && !input.fail()) try
	{
		control.HandleCommand();
	}
	catch (const exception& ex)
	{
		cerr << ex.what() << endl;
	}

	control.PrintInfo(cout);
}