#pragma once
#include <boost/noncopyable.hpp>
#include "Point.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"

class CShapesController : boost::noncopyable
{
public:
	CShapesController(std::vector<std::shared_ptr<IShape>>& shapes);
	void HandleCommand(std::string commandLine) const;
	void PrintInfo(std::ostream & output) const;
private:
	void CreateLine(std::istream & args);
	void CreateTriangle(std::istream & args);
	void CreateRectangle(std::istream & args);
	void CreateCircle(std::istream & args);
	typedef std::map<std::string, std::function<void(std::istream & args)>> ActionMap;

	std::vector<std::shared_ptr<IShape>>* m_shapes;
	const ActionMap m_actionMap;
};

std::istream & operator >> (std::istream & stream, std::shared_ptr<CLineSegment> & line);
std::istream & operator >> (std::istream & stream, std::shared_ptr<CTriangle> & triangle);
std::istream & operator >> (std::istream & stream, std::shared_ptr<CRectangle> & rectangle);
std::istream & operator >> (std::istream & stream, std::shared_ptr<CCircle> & circle);