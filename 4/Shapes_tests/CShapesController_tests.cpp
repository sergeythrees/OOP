#include "stdafx.h"

using namespace std;

struct ShapesControllerFixture
{
	CShapesController controller;
	vector<shared_ptr<IShape>> shapes;

	ShapesControllerFixture()
		:shapes(vector<shared_ptr<IShape>>()),
		controller{shapes}
	{}
};
BOOST_FIXTURE_TEST_SUITE(CShapesController_, ShapesControllerFixture)
	BOOST_AUTO_TEST_SUITE(input_from_stream_operator_functions_should_work_correctly)
		BOOST_AUTO_TEST_CASE(with_CLineSegment)
		{
			shared_ptr<CLineSegment> line;
			Point expectedPointA{ 12, 34 };
			Point expectedPointB{ 32, -5 };
			string expectedOutlineColor("red");
			stringstream stream;

			stream << expectedPointA.x << " " 
				   << expectedPointA.y << " "
				   << expectedPointB.x << " "
				   << expectedPointB.y << " "
				   << expectedOutlineColor;

			stream >> line;
			VerifyLine(*line, expectedPointA, expectedPointB, expectedOutlineColor);
		}
		BOOST_AUTO_TEST_CASE(with_CTriangle)
		{
			shared_ptr<CTriangle> triangle;
			Point expectedPointA{ 12, 34 };
			Point expectedPointB{ 32, -5 };
			Point expectedPointC{ 0, 1 };
			string expectedOutlineColor("blue");
			string expectedFillColor("blue");
			stringstream stream;

			stream << expectedPointA.x << " "
				<< expectedPointA.y << " "
				<< expectedPointB.x << " "
				<< expectedPointB.y << " "
				<< expectedPointC.x << " "
				<< expectedPointC.y << " "
				<< expectedOutlineColor << " "
				<< expectedFillColor;

			stream >> triangle;
			VerifyTriangle(*triangle, expectedPointA, expectedPointB, expectedPointC, 
				expectedOutlineColor, expectedFillColor);
		}

		BOOST_AUTO_TEST_CASE(with_CRectangle)
		{
			shared_ptr<CRectangle> rectangle;
			Point expectedLeftBottom{ 12, 34 };
			double expectedWidth(5);
			double expectedHeight(3);
			string expectedOutlineColor("blue");
			string expectedFillColor("blue");
			stringstream stream;

			stream << expectedLeftBottom.x << " "
				<< expectedLeftBottom.y << " "
				<< expectedWidth << " "
				<< expectedHeight << " "
				<< expectedOutlineColor << " "
				<< expectedFillColor;

			stream >> rectangle;
			VerifyRectangle(*rectangle, expectedLeftBottom, expectedWidth, expectedHeight,
				expectedOutlineColor, expectedFillColor);
		}

		BOOST_AUTO_TEST_CASE(with_CCircle)
		{
			shared_ptr<CCircle> circle;
			Point expectedCenter{ 12, 34 };
			double expectedRadius(5);
			string expectedOutlineColor("blue");
			string expectedFillColor("blue");
			stringstream stream;

			stream << expectedCenter.x << " "
				<< expectedCenter.y << " "
				<< expectedRadius << " "
				<< expectedOutlineColor << " "
				<< expectedFillColor;

			stream >> circle;
			VerifyCircle(*circle, expectedCenter, expectedRadius, 
				expectedOutlineColor, expectedFillColor);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()