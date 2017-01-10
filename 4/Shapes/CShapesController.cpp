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

std::istream & operator >> (std::istream & stream, shared_ptr<CLineSegment> & line)
{
	double Ax;
	double Ay;
	double Bx;
	double By;
	std::string outlineColor;
	if (
		stream >> Ax &&
		stream >> Ay &&
		stream >> Bx &&
		stream >> By &&
		stream >> outlineColor)
	{
		line = make_shared<CLineSegment>(CLineSegment({ Ax,Ay }, { Bx, By }, outlineColor));
	}
	else
	{

		stream.setstate(std::ios_base::failbit);
		stringstream mess;
		mess << "Invalid arguments." << endl
			<< "Use: <Ax> <Ay> <Bx> <By> <outlineColor>" << endl;
		throw(invalid_argument(mess.str()));
	}

	return stream;
}

std::istream & operator >> (std::istream & stream, std::shared_ptr<CTriangle> & triangle)
{
	double Ax;
	double Ay;
	double Bx;
	double By;
	double Cx;
	double Cy;

	string outlineColor;
	string fillColor;
	if (
		stream >> Ax &&
		stream >> Ay &&
		stream >> Bx &&
		stream >> By &&
		stream >> Cx &&
		stream >> Cy &&
		stream >> outlineColor&&
		stream >> fillColor)
	{
		triangle = make_shared<CTriangle>(CTriangle({ Ax,Ay }, { Bx, By }, { Cx, Cy }, outlineColor, fillColor));
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
		stringstream mess;
		mess << "Invalid arguments." << endl
			<< "Use: <Ax> <Ay> <Bx> <By> <Cx> <Cy> <outlineColor> <fillColor>" << endl;
		throw(invalid_argument(mess.str()));
	}

	return stream;
}

std::istream & operator >> (std::istream & stream, std::shared_ptr<CRectangle> & rectangle)
{
	double Ax;
	double Ay;
	double width;
	double height;
	string outlineColor;
	string fillColor;
	if (
		stream >> Ax &&
		stream >> Ay &&
		stream >> width &&
		stream >> height &&
		stream >> outlineColor&&
		stream >> fillColor)
	{
		rectangle = make_shared<CRectangle>(CRectangle({ Ax,Ay }, width, height, outlineColor, fillColor));
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
		stringstream mess;
		mess << "Invalid arguments." << endl
			<< "Use: <LeftBottom.x> <LeftBottom.y> <width> <height> <outlineColor> <fillColor>" << endl;
		throw(invalid_argument(mess.str()));
	}

	return stream;
}

std::istream & operator >> (std::istream & stream, std::shared_ptr<CCircle> & circle)
{
	double Ax;
	double Ay;
	double radius;
	std::string outlineColor;
	string fillColor;
	if (
		stream >> Ax &&
		stream >> Ay &&
		stream >> radius &&
		stream >> outlineColor&&
		stream >> fillColor)
	{
		circle = make_shared<CCircle>(CCircle({ Ax, Ay }, radius, outlineColor, fillColor));
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
		stringstream mess;
		mess << "Invalid arguments." << endl
			<< "Use: <Ox> <Oy> <radius> <outlineColor> <fillColor>" << endl;
		throw(invalid_argument(mess.str()));
	}

	return stream;
}

