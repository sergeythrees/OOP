#include "stdafx.h"
#include "CShapesController.h"

#include "FindMaxEx.h"
#include <boost/algorithm/string.hpp>
#define CREATE_SHAPE_FUNCTION(function) {\
	[&](std::istream & args) {this->function(args); }}

using namespace std;

CShapesController::CShapesController(std::vector<std::shared_ptr<IShape>>& shapes, std::istream & input)
	:m_shapes(&shapes),
	m_input(input),
	m_actionMap({
	{ "line", CREATE_SHAPE_FUNCTION(CreateLine) },
	{ "triangle", CREATE_SHAPE_FUNCTION(CreateTriangle) },
	{ "rectangle", CREATE_SHAPE_FUNCTION(CreateRectangle) },
	{ "circle", CREATE_SHAPE_FUNCTION(CreateCircle) }
	})
{
}

void CShapesController::HandleCommand() const
{
	string commandLine;
	getline(m_input, commandLine);
	if (cin.eof() || cin.fail())
		return;
	istringstream strm(commandLine);
	string action;
	if (strm >> action &&
		!action.empty() &&
		m_actionMap.count(action) > 0)
	{
		m_actionMap.at(action)(strm);
	}
	else
	{
		stringstream mess;
		mess << "Incorrect or empty command" << endl;
		throw(invalid_argument(mess.str()));
	}
	
}

void CShapesController::PrintInfo(std::ostream & output) const
{
	if (m_shapes->empty())
	{
		throw(invalid_argument("Array is empty"));
	}

	auto maxArea = FindMaxEx(*m_shapes,
				[&](const shared_ptr<IShape>& a, const shared_ptr<IShape>& b)
			{return a->GetArea() < b->GetArea(); });
	auto maxPerimeter = FindMaxEx(*m_shapes,
				[&](const shared_ptr<IShape>& a, const shared_ptr<IShape>& b)
			{return a->GetPerimeter() > b->GetPerimeter(); });

	if (maxArea && maxPerimeter)
	{
		output << "Shape with max area:"
			<< (*maxArea)->ToString() << endl
			<< "Shape with min perimeter:"
			<< (*maxPerimeter)->ToString() << endl;
	}
}

void CShapesController::CreateLine(std::istream & args)
{
	std::shared_ptr<CLineSegment> line;
	args >> line;
	m_shapes->push_back(line);
}

void CShapesController::CreateTriangle(std::istream & args)
{
	std::shared_ptr<CTriangle> triangle;
	args >> triangle;
	m_shapes->push_back(triangle);
}

void CShapesController::CreateRectangle(std::istream & args)
{
	std::shared_ptr<CRectangle> rectangle;
	args >> rectangle;
	m_shapes->push_back(rectangle);
}

void CShapesController::CreateCircle(std::istream & args)
{
	std::shared_ptr<CCircle> circle;
	args >> circle;
	m_shapes->push_back(circle);
}

