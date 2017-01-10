#include "stdafx.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CShapesController_)
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
	
	struct ShapesControllerFixture
	{
		CShapesController controller;
		vector<shared_ptr<IShape>> shapes;
		stringstream input;

		ShapesControllerFixture()
			:shapes(vector<shared_ptr<IShape>>()),
			input(stringstream()),
			controller(shapes, input)
		{}
	};

	BOOST_FIXTURE_TEST_SUITE(_, ShapesControllerFixture)
		BOOST_AUTO_TEST_SUITE(HandleCommand_function)
			BOOST_AUTO_TEST_CASE(can_create_line)
			{
				input << "line 12 23 4 -3 red";
				controller.HandleCommand();
				BOOST_CHECK(shapes.size() == 1);
			}

			BOOST_AUTO_TEST_CASE(can_create_triangle)
			{
				input << "triangle 12 23 4 3 0 0 blue white";
				controller.HandleCommand();
				BOOST_CHECK(shapes.size() == 1);
			}

			BOOST_AUTO_TEST_CASE(can_create_rectangle)
			{
				input << "rectangle 12 23 4 3 blue white";
				controller.HandleCommand();
				BOOST_CHECK(shapes.size() == 1);
			}

			BOOST_AUTO_TEST_CASE(can_create_circle)
			{
				input << "circle 12 23 4.2 blue white";
				controller.HandleCommand();
				BOOST_CHECK(shapes.size() == 1);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(PrintInfo_output_shapes_with_max_area_and_min_perimeter)
		{
			input << "circle 12 23 4.2 blue white " << endl
				<< "rectangle 12 23 4 3 blue white " << endl
				<< "triangle 12 23 4 3 0 0 blue white " << endl
				<< "line 12 23 4 -3 red";

			controller.HandleCommand();
			controller.HandleCommand();
			controller.HandleCommand();
			controller.HandleCommand();

			BOOST_CHECK_EQUAL(shapes.size(), static_cast<size_t>(4));

			ostringstream output;
			stringstream expectedOutput;
			expectedOutput << "Shape with max area:"
				<< shapes[0]->ToString() << endl
				<< "Shape with min perimeter:"
				<< shapes[1]->ToString() << endl;

			controller.PrintInfo(output);

			BOOST_CHECK_EQUAL(output.str(), expectedOutput.str());

		}

		BOOST_AUTO_TEST_SUITE(should_throw_appropriate_exceptions_)
			BOOST_AUTO_TEST_CASE(when_input_is_incorrect)
			{
				auto handle = [&]() { controller.HandleCommand(); };

				input << "circle" << endl
					<< "rectangle " << endl
					<< "triangle <incorrect_argumets>" << endl
					<< "line <incorrect_argumets>" << endl
					<< "unknown_command";

				VerifyException<invalid_argument>(handle,
					"Invalid arguments.\nUse: <Ox> <Oy> <radius> <outlineColor> <fillColor>\n");

				VerifyException<invalid_argument>(handle,
					"Invalid arguments.\nUse: <LeftBottom.x> <LeftBottom.y> <width> <height> <outlineColor> <fillColor>\n");

				VerifyException<invalid_argument>(handle,
					"Invalid arguments.\nUse: <Ax> <Ay> <Bx> <By> <Cx> <Cy> <outlineColor> <fillColor>\n");

				VerifyException<invalid_argument>(handle,
					"Invalid arguments.\nUse: <Ax> <Ay> <Bx> <By> <outlineColor>\n");

				VerifyException<invalid_argument>(handle,
					"Incorrect or empty command\n");

				BOOST_CHECK(shapes.size() == 0);
			}
			BOOST_AUTO_TEST_CASE(when_Print_info_function_run_with_incorrect_shapes_array)
			{
				stringstream output;
				auto printInfo = [&]() { controller.PrintInfo(output); };

				VerifyException<invalid_argument>(printInfo,
					"Array is empty");

				BOOST_CHECK(output.str().empty());
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()