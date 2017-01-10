#pragma once
#include "Point.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <boost/noncopyable.hpp>

class CShapesController : boost::noncopyable
{
public:
	CShapesController(std::vector<std::shared_ptr<IShape>>& shapes, std::istream & input);
	void HandleCommand() const;
	void PrintInfo(std::ostream & output) const;
private:
	void CreateLine(std::istream & args);
	void CreateTriangle(std::istream & args);
	void CreateRectangle(std::istream & args);
	void CreateCircle(std::istream & args);
	typedef std::map<std::string, std::function<void(std::istream & args)>> ActionMap;

	std::vector<std::shared_ptr<IShape>>* m_shapes;
	std::istream & m_input;
	const ActionMap m_actionMap;
};
