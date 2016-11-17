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

void CCar::SetDirection()
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

bool CCar::SetGear(Gear gear)
{
	if (!m_isTurnedOn)
	{
		if (gear == NEUTRAL)
			return true;
		else
			return false;
	}
		
	if (gear == m_gear)
		return true;

	switch (gear)
	{
	case REVERSE:
		if ((m_gear == NEUTRAL) || ((m_gear == FIRST) && (m_speed == 0)))
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
		if (((m_gear == NEUTRAL) && (m_speed == 0)) || ((m_gear == REVERSE) && (m_speed == 0)) || (m_gear == SECOND))
		{
			m_gear = gear;
			return true;
		}
		break;
	case SECOND:
		if ((m_gear == FIRST) || (m_gear == THIRD))
		{
			m_gear = gear;
			return true;
		}
		break;
	case THIRD:
		if ((m_gear == SECOND) || (m_gear == FOURTH))
		{
			m_gear = gear;
			return true;
		}
		break;
	case FOURTH:
		if ((m_gear == THIRD) || (m_gear == FIFTH))
		{
			m_gear = gear;
			return true;
		}
		break;
	case FIFTH:
		if ((m_gear == FOURTH))
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
	case REVERSE:
		if ((speed >= 0) && (speed <= 20))
		{
			m_speed = speed;
		}
		break;
	case NEUTRAL:
			if (speed <= m_speed)
			{
				m_speed = speed;
			}
		break;
	case FIRST:
		if ((speed >= 0) && (speed <= 30))
		{
			m_speed = speed;
		}
		break;
	case SECOND:
		if ((speed >= 20) && (speed <= 50))
		{
			m_speed = speed;
		}
		break;
	case THIRD:
		if ((speed >= 30) && (speed <= 60))
		{
			m_speed = speed;
		}
		break;
	case FOURTH:
		if ((speed >= 40) && (speed <= 90))
		{
			m_speed = speed;
		}
		break;
	case FIFTH:
		if ((speed >= 50) && (speed <= 150))
		{
			m_speed = speed;
		}
		break;
	}

	SetDirection();
	return m_speed == speed;
}

bool CCar::IsSpeedInRange(int speed, Gear currentGear) const
{
	return false;
}