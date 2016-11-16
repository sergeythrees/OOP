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
	return m_direction;
}

void CCar::SetDirection()
{
	if ((m_speed > 0) && (m_speed <= 150))
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

bool CCar::SetGear(Gear gear)
{
	switch (gear)
	{
	case REVERSE:
		if ((m_gear == NEUTRAL) || (m_gear == REVERSE))
		{
			m_gear = gear;
			return true;
		}
		break;
	case NEUTRAL:
		if ((m_gear == NEUTRAL) || (m_gear == FIRST) || (m_gear == REVERSE))
		{
			m_gear = gear;
			return true;
		}
		break;
	case FIRST:
		if ((m_gear == NEUTRAL) || (m_gear == SECOND))
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
	switch (m_gear)
	{
	case FIRST:
		if ((speed >= 0) && (speed <= 30))
		{
			m_speed = speed;
			SetDirection();
			return true;
		}
		break;
	}
	return false;
}

bool CCar::IsSpeedInRange(int speed, Gear currentGear) const
{
	return false;
}