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

bool CCar::IsSpeedInRange(int speed, Gear currentGear) const
{
	switch (currentGear)
	{
	case REVERSE:
		if ((speed >= 0) && (speed <= 20))
		{
			return true;
		}
		break;
	case NEUTRAL:
		if (speed <= m_speed)
		{
			return true;
		}
		break;
	case FIRST:
		if ((speed >= 0) && (speed <= 30))
		{
			return true;
		}
		break;
	case SECOND:
		if ((speed >= 20) && (speed <= 50))
		{
			return true;
		}
		break;
	case THIRD:
		if ((speed >= 30) && (speed <= 60))
		{
			return true;
		}
		break;
	case FOURTH:
		if ((speed >= 40) && (speed <= 90))
		{
			return true;
		}
		break;
	case FIFTH:
		if ((speed >= 50) && (speed <= 150))
		{
			return true;
		}
		break;
	default:
		return false;
	}

	return false;
}