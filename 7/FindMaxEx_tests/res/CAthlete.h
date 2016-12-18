#pragma once
#include <string>

class CAthlete
{
public:
	CAthlete(const std::string & name, double height, double weight)
		: m_name(name), m_height(height), m_weight(weight) {};
	CAthlete() : CAthlete(std::string(), 0, 0) {};

	std::string Name() { return m_name; }
	double Height() { return m_height; }
	double Weight() { return m_weight; }
private:
	std::string m_name;
	double m_height;
	double m_weight;
};