#include "stdafx.h"
#include "../Car/Car.h"

using namespace std;

struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(After_construction_car, CarFixture)

	BOOST_AUTO_TEST_CASE(engine_must_be_turned_off)
	{
		BOOST_CHECK(!car.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(engine_can_be_turn_on)
	{
		BOOST_CHECK(car.TurnOnEngine());
		BOOST_CHECK(car.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(direction_must_be_as_NONE)
	{
		BOOST_CHECK(car.GetDirection() == NONE);
	}

	BOOST_AUTO_TEST_CASE(speed_should_be_zero)
	{
		BOOST_CHECK(car.GetSpeed() == 0);
	}

	BOOST_AUTO_TEST_CASE(can_not_set_speed)
	{
		BOOST_CHECK(!car.SetSpeed(10));
	}

	BOOST_AUTO_TEST_CASE(gear_must_be_as_NEUTRAL)
	{
		BOOST_CHECK(car.GetGear() == NEUTRAL);
	}

	BOOST_AUTO_TEST_CASE(must_not_turn_off_engine)
	{
		BOOST_CHECK(car.TurnOffEngine() == false);
	}

BOOST_AUTO_TEST_SUITE_END()