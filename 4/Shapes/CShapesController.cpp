#include "stdafx.h"
#include "FindMaxEx.h"
#include "CShapesController.h"
#define CREATE_SHAPE_FUNCTION(function) {\
	[&](std::istream & args) {this->function(args); }}

using namespace std;

CShapesController::CShapesController(std::vector<std::shared_ptr<IShape>>& shapes)
	:m_shapes(&shapes),
	m_actionMap({
	{ "line", CREATE_SHAPE_FUNCTION(CreateLine) },
	{ "triangle", CREATE_SHAPE_FUNCTION(CreateTriangle) },
	{ "rectangle", CREATE_SHAPE_FUNCTION(CreateRectangle) },
	{ "circle", CREATE_SHAPE_FUNCTION(CreateCircle) }
	})
{
}

void CShapesController::HandleCommand(std::string commandLine) const
{
	istringstream strm(commandLine);
	string action;
	strm >> action;
	if (strm.eof() && action.empty())
	{
		cerr << "Empty command" << endl;
		return;
	}
	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
	}
}

void CShapesController::PrintInfo(std::ostream & output) const
{
	if (m_shapes->empty())
	{
		cerr << "Array is empty" << endl;
		return;
	}

	for (auto current : *m_shapes)
	{
		output << current->ToString() << endl;
	}
	
	output << endl;

	auto maxArea = FindMaxEx(*m_shapes,
				[&](const shared_ptr<IShape>& a, const shared_ptr<IShape>& b)
			{return a->GetArea() < b->GetArea(); });
	auto maxPerimeter = FindMaxEx(*m_shapes,
				[&](const shared_ptr<IShape>& a, const shared_ptr<IShape>& b)
			{return a->GetPerimeter() < b->GetPerimeter(); });

	if (maxArea && maxPerimeter)
	{
		output << "Shape with max area:"
			<< (*maxArea)->ToString() << endl
			<< "Shape with max perimeter:"
			<< (*maxPerimeter)->ToString() << endl;
	}
	else
		cerr << "Error! Can'not search in array" << endl;
}

void CShapesController::CreateLine(std::istream & args)
{
	std::shared_ptr<CLineSegment> line;
	if (args >> line )
	{
		m_shapes->push_back(line);
	}
	else
		cerr << "Invalid arguments." << endl
			 << "Use: <Ax> <Ay> <Bx> <By> <outlineColor>" << endl;
}

void CShapesController::CreateTriangle(std::istream & args)
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
		args >> Ax &&
		args >> Ay &&
		args >> Bx &&
		args >> By &&
		args >> Cx &&
		args >> Cy &&
		args >> outlineColor&&
		args >> fillColor)
	{
		m_shapes->push_back(make_shared<CTriangle>(CTriangle({ Ax,Ay }, { Bx, By }, { Cx, Cy }, outlineColor, fillColor)));
	}
	else
		cerr << "Invalid arguments." << endl
		<< "Use: <Ax> <Ay> <Bx> <By> <Cx> <Cy> <outlineColor> <fillColor>" << endl;
}

void CShapesController::CreateRectangle(std::istream & args)
{
	double Ax;
	double Ay;
	double width;
	double height;
	string outlineColor;
	string fillColor;
	if (
		args >> Ax &&
		args >> Ay &&
		args >> width &&
		args >> height &&
		args >> outlineColor&&
		args >> fillColor)
	{
		m_shapes->push_back(make_shared<CRectangle>(CRectangle({ Ax,Ay }, width, height, outlineColor, fillColor)));
	}
	else
		cerr << "Invalid arguments." << endl
		<< "Use: <Ax> <Ay> <Bx> <By> <Cx> <Cy> <outlineColor> <fillColor>" << endl;
}

void CShapesController::CreateCircle(std::istream & args)
{
	string kek;
	getline(args, kek);
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
		circle = make_shared<CCircle>(CCircle({ Ax, Ay}, radius, outlineColor, fillColor));
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
	}

	return stream;
}