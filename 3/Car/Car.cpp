#include "stdafx.h"
#include "Car.h"

bool CCar::isTurnedOn() const
{
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

int CCar::GetGear() const
{
	return 0;
}

bool CCar::TurnOnEngine()
{
	return false;
}

bool CCar::TurnOffEngine()
{
	return false;
}

bool CCar::SetGear(int gear)
{
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