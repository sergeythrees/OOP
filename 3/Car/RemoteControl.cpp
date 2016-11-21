#include "stdafx.h"
#include "RemoteControl.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CCar & car, std::istream & input, std::ostream & output) 
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap
	({
		{ "EngineOn", [this](istream & strm) { return EngineOn(strm); } },
		{ "EngineOff", [this](istream & strm) { return EngineOff(strm); } },
		{ "SetGear", [this](istream & strm) { return SetGear(strm); } },
		{ "SetSpeed", [this](istream & strm) { return SetSpeed(strm); } },
		{ "Info", [this](istream & strm) { return Info(strm); } }
	})
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	m_input >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CRemoteControl::EngineOn(std::istream & args)
{
	bool isTurnOnEngine = m_car.TurnOnEngine();
	m_output << isTurnOnEngine ? "Engine is turned on\n" : "Engine is already on!\n";
	return isTurnOnEngine;
}

bool CRemoteControl::EngineOff(std::istream & args)
{
	bool isTurnOff = m_car.TurnOffEngine();
	m_output << isTurnOff ? "Engine is turned off\n" : "Engine is already off, not on neutral gear or not carero speed!\n";
	return isTurnOff;
}

bool CRemoteControl::SetGear(std::istream & args)
{
	int gear;
	args >> gear;
	bool isSetGear = m_car.SetGear(FIRST);
	m_output << isSetGear ? "Gear: " + std::to_string(m_car.GetGear()) : "Error: Gear can not switch at the moment!";
	return isSetGear;
}

bool CRemoteControl::SetSpeed(std::istream & args)
{
	int speed;
	args >> speed;
	bool isSetSpeed = m_car.SetSpeed(speed);
	m_output << isSetSpeed ? "Speed: " + std::to_string(m_car.GetSpeed()) : "Error: Speed is not the same as a valid gear value or gear is neutral!";
	return isSetSpeed;
}

bool CRemoteControl::Info(std::istream & /*args*/)
{
	std::string output = m_car.IsTurnedOn() ?
		"Engine is turned on\n"
		"Direction: " + GetDirectionString(m_car.GetDirection()) + "\n"
		"Gear: " + std::to_string(m_car.GetGear()) + "\n"
		"Speed: " + std::to_string(m_car.GetSpeed()) + "\n"
		: "Engine is turned off\n";
	m_output << output;
	return true;
}

string CRemoteControl::GetDirectionString(Direction const& direction)
{
	std::string result;
	if (direction == Direction::FORWARD)
	{
		result = "Forward";
	}
	else if (direction == Direction::BACKWARD)
	{
		result = "Backward";
	}
	else
	{
		result = "Standing";
	}
	return result;
}