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

void CShapesController::PrintInfo(std::ostream & output)
{
	for (auto current : *m_shapes)
	{
		output << current->ToString() << endl;
	}
}

void CShapesController::CreateLine(std::istream & args)
{
	double Ax, Ay, Bx, By;
	string outlineColor;
	if (
		args >> Ax &&
		args >> Ay &&
		args >> Bx &&
		args >> By &&
		args >> outlineColor)
	{
		m_shapes->push_back(make_shared<CLineSegment>( CLineSegment({ Ax,Ay }, { Bx, By }, outlineColor)));
	}
	else
		cerr << "Invalid arguments." << endl
			 << "Use: <x1> <y1> <x2> <y2> <colorOutline>" << endl;
}

void CShapesController::CreateTriangle(std::istream & args)
{
	string kek;
	getline(args, kek);
}

void CShapesController::CreateRectangle(std::istream & args)
{
	string kek;
	getline(args, kek);
}

void CShapesController::CreateCircle(std::istream & args)
{
	string kek;
	getline(args, kek);
}

