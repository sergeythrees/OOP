#pragma once
enum Direction {NONE, FORWARD, BACKWARD};
enum Gear 
{
	REVERSE = -1,
	NEUTRAL = 0,
	FIRST = 1,
	SECOND = 2,
	THIRD = 3,
	FOURTH = 4,
	FIFTH = 5
};

class CCar
{
public:

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
private:
	bool IsSpeedInRange(int speed, Gear currentGear) const;

	bool m_isTurnedOn = false;
	Direction m_direction = NONE;
	int m_speed = 0;
	Gear m_gear = NEUTRAL;
};

