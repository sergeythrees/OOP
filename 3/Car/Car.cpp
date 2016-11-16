#include "stdafx.h"
#include "Car.h"

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
	return Direction();
}

int CCar::GetSpeed() const
{
	return 0;
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
	return false;
}

bool CCar::SetGear(Gear gear)
{
	switch (gear)
	{
	case NEUTRAL:
		if ((m_gear == NEUTRAL) || (m_gear == FIRST) || (m_gear == REVERSE))
		{
			m_gear = gear;
			return true;
		}
		break;
	case REVERSE:
		if ((m_gear == NEUTRAL) || (m_gear == REVERSE))
		{
			m_gear = gear;
			return true;
		}
		break;
	}
		

	return false;
}

bool CCar::SetSpeed(int speed)
{
	return false;
}

bool CCar::IsSpeedInRange(int speed, Gear currentGear) const
{
	return false;
}