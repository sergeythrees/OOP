#include "stdafx.h"
#include "CarControl.h"
#include <algorithm>

using namespace std;

CCarControl::CCarControl(CCar & car, std::istream & input, std::ostream & output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap
	({
		{ "engineon", [this](istream & strm) { return EngineOn(strm); } },
		{ "engineoff", [this](istream & strm) { return EngineOff(strm); } },
		{ "setgear", [this](istream & strm) { return SetGear(strm); } },
		{ "setspeed", [this](istream & strm) { return SetSpeed(strm); } },
		{ "info", [this](istream & strm) { return Info(strm); } }
})
{
}

void CCarControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	std::transform(commandLine.begin(), commandLine.end(), commandLine.begin(), tolower);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
	}
	else
		m_output << "Unknown command!\n";
}

bool CCarControl::EngineOn(std::istream & args)
{
	bool isTurnOn = m_car.TurnOnEngine();

	if (isTurnOn)
	{
		m_output << "Engine is turned on" << endl;
	}
	else
		m_output << "Engine is already on!" << endl;

	return isTurnOn;
}

bool CCarControl::EngineOff(std::istream & args)
{
	bool isTurnOff = m_car.TurnOffEngine();

	if (isTurnOff)
	{
		m_output << "Engine is turned off" << endl;
	}
	else
		m_output << "Engine is already off, gear is not NEUTRAL or speed is not zero!" << endl;

	return isTurnOff;
}

bool CCarControl::SetGear(std::istream & args)
{
	int newGear = 0;
	bool isSetGear = false;

	if (args >> newGear)
	{
		isSetGear = m_car.SetGear(newGear);
		if (isSetGear)
		{
			m_output << "Gear: " << to_string(m_car.GetGear()) << endl;
		}
		else
		{
			if (!m_car.IsTurnedOn())
				m_output << "Engine is turned off" << endl;
			m_output << "Gear can not switch to this value!" << endl;
		}
	}
	else
	{
		m_output << "Invalid argument" << endl;
	}


	return isSetGear;
}

bool CCarControl::SetSpeed(std::istream & args)
{
	int newSpeed = 0;
	bool isSetSpeed = false;

	if (args >> newSpeed)
	{
		isSetSpeed = m_car.SetSpeed(newSpeed);
		if (isSetSpeed)
		{
			m_output << "Speed: " << to_string(m_car.GetSpeed()) << endl;
		}
		else
		{
			if (!m_car.IsTurnedOn())
				m_output << "Engine is turned off" << endl;
			m_output << "This speed value is not included in the valid range of the " << to_string(m_car.GetGear()) << " gear!" << endl;
		}
	}
	else
	{
		m_output << "Invalid argument" << endl;
	}
		
	return isSetSpeed;
}

bool CCarControl::Info(std::istream & /*args*/)
{
	if (m_car.IsTurnedOn())
	{
		m_output << "Engine is turned on" << endl
			<< "Direction: " << DirectionToString(m_car.GetDirection()) << endl
			<< "Gear: " << to_string(m_car.GetGear()) << endl
			<< "Speed: " << to_string(m_car.GetSpeed()) << endl;
	}
	else
		m_output << "Engine is turned off" << endl;

	return true;
}

string CCarControl::DirectionToString(Direction direction)
{
	string result;
	switch (direction)
	{
	case BACKWARD:
		result = "BACKWARD";
		break;
	case NONE:
		result = "NONE";
		break;
	case FORWARD:
		result = "FORWARD";
		break;
	}

	return result;
}