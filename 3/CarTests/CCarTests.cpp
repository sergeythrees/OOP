#include "stdafx.h"
#include "../Car/Car.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Car_class)

	struct CarFixture
	{
		CCar car;
	};

	BOOST_FIXTURE_TEST_SUITE(After_construction_car, CarFixture)

		BOOST_AUTO_TEST_CASE(engine_must_be_turned_off)
		{
			BOOST_CHECK(!car.IsTurnedOn());
		}

		BOOST_AUTO_TEST_CASE(direction_must_be_as_NONE)
		{
			BOOST_CHECK(car.GetDirection() == NONE);
		}

		BOOST_AUTO_TEST_CASE(speed_should_be_zero)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
		}

		BOOST_AUTO_TEST_CASE(gear_must_be_as_NEUTRAL)
		{
			BOOST_CHECK(car.GetGear() == NEUTRAL);
		}

	BOOST_AUTO_TEST_SUITE_END()


	BOOST_FIXTURE_TEST_SUITE(When_turned_off_engine, CarFixture)

		BOOST_AUTO_TEST_CASE(can_not_turn_off_engine)
		{
			BOOST_CHECK(car.TurnOffEngine() == false);
		}

		BOOST_AUTO_TEST_CASE(engine_can_be_turn_on)
		{
			BOOST_CHECK(car.TurnOnEngine());
			BOOST_CHECK(car.IsTurnedOn());
		}
		BOOST_AUTO_TEST_CASE(can_not_set_speed)
		{
			BOOST_CHECK(!car.SetSpeed(10));
		}

		BOOST_AUTO_TEST_CASE(can_set_gear_only_to_NEUTRAL)
		{
			BOOST_CHECK(car.SetGear(NEUTRAL));
			BOOST_CHECK(!car.SetGear(REVERSE));
			BOOST_CHECK(!car.SetGear(FIRST));
			BOOST_CHECK(!car.SetGear(FIFTH));
		}

	BOOST_AUTO_TEST_SUITE_END()
		

	struct when_turned_on_engine : CarFixture
	{
		when_turned_on_engine()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(When_turned_on_engine, when_turned_on_engine)

		BOOST_AUTO_TEST_CASE(can_not_turn_on_engine)
		{
			BOOST_CHECK(!car.TurnOnEngine());
		}

		BOOST_AUTO_TEST_CASE(can_turn_off_engine_only_if_gear_is_NEUTRAL_and_speed_is_zero)
		{
			BOOST_CHECK(car.TurnOffEngine());

			car.SetGear(FIRST);
			BOOST_CHECK(!car.TurnOffEngine());

			car.SetSpeed(20);
			BOOST_CHECK(!car.TurnOffEngine());
		}

		BOOST_AUTO_TEST_CASE(direction_must_be_FORWARD_if_speed_greater_than_zero)
		{
			car.SetGear(FIRST);
			car.SetSpeed(20);
			BOOST_CHECK(car.GetDirection() == FORWARD);
		}

		BOOST_AUTO_TEST_CASE(direction_must_be_NONE_if_speed_is_zero)
		{
			car.SetGear(FIRST);
			car.SetSpeed(20);
			car.SetGear(NEUTRAL);
			car.SetSpeed(0);
			BOOST_CHECK(car.GetDirection() == NONE);
		}

		BOOST_AUTO_TEST_CASE(direction_must_be_BACKWARD_if_speed_less_than_zero)
		{
			car.SetGear(REVERSE);
			car.SetSpeed(20);
			BOOST_CHECK(car.GetDirection() == BACKWARD);
		}

		BOOST_AUTO_TEST_CASE(can_set_speed_only_within_the_corresponding_gear_range)
		{
			BOOST_CHECK(car.SetGear(REVERSE));
			BOOST_CHECK(car.SetSpeed(10));
			BOOST_CHECK(!car.SetSpeed(30));

			BOOST_CHECK(car.SetGear(NEUTRAL));
			BOOST_CHECK(!car.SetSpeed(20));
			BOOST_CHECK(car.SetSpeed(10));
			BOOST_CHECK(car.SetSpeed(0));

			BOOST_CHECK(car.SetGear(FIRST));
			BOOST_CHECK(car.SetSpeed(30));
			BOOST_CHECK(car.SetSpeed(20));
			BOOST_CHECK(!car.SetSpeed(40));

			BOOST_CHECK(car.SetGear(SECOND));
			BOOST_CHECK(car.SetSpeed(40));
			BOOST_CHECK(!car.SetSpeed(10));
			BOOST_CHECK(!car.SetSpeed(60));

			BOOST_CHECK(car.SetGear(THIRD));
			BOOST_CHECK(car.SetSpeed(60));
			BOOST_CHECK(!car.SetSpeed(20));
			BOOST_CHECK(!car.SetSpeed(70));

			BOOST_CHECK(car.SetGear(FOURTH));
			BOOST_CHECK(car.SetSpeed(90));
			BOOST_CHECK(!car.SetSpeed(30));
			BOOST_CHECK(!car.SetSpeed(100));

			BOOST_CHECK(car.SetGear(FIFTH));
			BOOST_CHECK(car.SetSpeed(100));
			BOOST_CHECK(!car.SetSpeed(40));
			BOOST_CHECK(!car.SetSpeed(160));

		}
		
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()