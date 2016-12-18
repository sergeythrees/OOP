#pragma once
#include <string>

class CAthlete
{
public:
	CAthlete(const std::string & name, double weight, double height) 
		: m_name(name), m_weight(weight), m_height(height) {};

	std::string Name() { return m_name; }
	double Weight() { return m_weight; }
	double Height() { return m_height; }
private:
	std::string m_name;
	double m_weight;
	double m_height;
};