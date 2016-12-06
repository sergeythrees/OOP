#include "stdafx.h"
#include <utility>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <map>
#include "Car.h"

std::map<Gear, std::pair<size_t, size_t>> gearSpeedsMap
{
	{ REVERSE,{ 0, 20 } },
	{ NEUTRAL,{ 0, 150 } },
	{ FIRST,{ 0, 30 } },
	{ SECOND,{ 20, 50 } },
	{ THIRD,{ 30, 60 } },
	{ FOURTH,{ 40, 90 } },
	{ FIFTH,{ 50, 150 } }
};

bool CCar::IsTurnedOn() const
{
	if (m_isTurnedOn)
	{
		return true;
	}
	return false;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

int CCar::GetSpeed() const
{
	return m_speed;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

bool CCar::TurnOnEngine()
{
	if (m_isTurnedOn == false)
	{
		m_isTurnedOn = true;
		return true;
	}
	return false;
}

bool CCar::TurnOffEngine()
{
	if ((m_gear == NEUTRAL) && (m_speed == 0) && (m_isTurnedOn))
	{
		m_isTurnedOn = false;
		return true;
	}
	return false;
}

void CCar::SetMovementDirection()
{
	if ((m_speed > 0) && (m_speed <= 150) && (m_gear != REVERSE))
	{
		m_direction = FORWARD;
	}
	else if ((m_speed > 0) && (m_speed <= 20) && (m_gear == REVERSE))
	{
		m_direction = BACKWARD;
	}
	else if (m_speed == 0)
	{
		m_direction = NONE;
	}
}

bool CCar::IsValidGear(Gear currentGear) const
{
	return (
		((m_gear >= NEUTRAL) && (currentGear >= NEUTRAL) && (m_speed >= 0)) ||
		((currentGear >= REVERSE) && (currentGear <= FIRST) && (m_speed == 0)) ||
		((currentGear == NEUTRAL))
		);
}

bool CCar::SetGear(int newGear)
{
	if (m_isTurnedOn)
	{
		if (IsSpeedInRange(m_speed, static_cast<Gear>(newGear)) && IsValidGear(static_cast<Gear>(newGear)))
		{
			m_gear = static_cast<Gear>(newGear);
			return true;
		}
		
	}
	else if (newGear == NEUTRAL)
	{
		m_gear = NEUTRAL;
		return true;
	}

	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (IsSpeedInRange(speed, m_gear))
	{
		m_speed = speed;
		SetMovementDirection();
	}

	return m_speed == speed;
}

bool CCar::IsSpeedInRange(int speed, Gear gear) const
{
	bool isSpeedInRange = false;
	auto currentGear = gearSpeedsMap.find(gear);

	if (currentGear != gearSpeedsMap.end())
	{
		if (speed >= currentGear->second.first && speed <= currentGear->second.second)
		{
			isSpeedInRange = true;
			if ((gear == NEUTRAL) && !(speed <= m_speed))
				isSpeedInRange = false;
		}
	}

	return isSpeedInRange;
}