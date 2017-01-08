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

//IShape * CShapesController::FindMaxArea() const
//{
//	return FindMaxEx(*m_shapes,
//		[&](const IShape& a, const IShape& b)
//	{return a.GetArea() > b.GetArea(); });
//}
//
//size_t CShapesController::FindMaxPerimeter() const
//{
//	return FindMaxEx(*m_shapes,
//		[&](const IShape& a, const IShape& b)
//	{return a.GetPerimeter() > b.GetPerimeter(); });
//}

//void CShapesController::PrintInfo(std::ostream & output)
//{
//	if (m_shapes->empty())
//		cerr << "Array is empty" << endl;
//	IShape* maxArea = FindMaxArea();
//	IShape* maxPerimeter = FindMaxPerimeter();
//	if (maxArea && maxPerimeter)
//	{
//		output << "Shape with max area:"
//			<< (*maxArea).ToString() << endl
//			<< "Shape with max perimeter:"
//			<< (*maxPerimeter).ToString() << endl;
//	}
//	else
//		cerr << "Error! Can'not search in array" << endl;
//
//}