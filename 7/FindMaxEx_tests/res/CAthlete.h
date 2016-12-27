#pragma once
#include <string>

class CAthlete
{
public:
	CAthlete(const std::string & name, double height, double weight)
		: m_name(name), m_height(height), m_weight(weight) {};
	CAthlete() : CAthlete(std::string(), 0, 0) {};

	std::string Name() const { return m_name; }
	double Height() const { return m_height; }
	double Weight() const { return m_weight; }

private:
	std::string m_name;
	double m_height;
	double m_weight;
};

bool operator ==(const CAthlete& a, const CAthlete& b)
{
	return (a.Name() == b.Name() && a.Height() == b.Height() && a.Weight() == b.Weight());
}

class iWillBeThrown
{
public:
	iWillBeThrown(bool switcher, std::string name)
		: m_TurnOnExceptionThrow(switcher),
		m_name(name) {}

	void operator=(const iWillBeThrown& b)
	{
		if (!m_TurnOnExceptionThrow)
			throw std::exception("I warned.");
		else
			m_name = b.m_name;
	}

	std::string Name() { return m_name; }
private:
	bool m_TurnOnExceptionThrow = false;
	std::string m_name;
};