#include "stdafx.h"
#include "../Car/CarControl.h"
#include "../Car/Car.h"
#include <sstream>

using namespace std;

struct CarControlDependencies
{
	CCar car;
	stringstream input;
	stringstream output;
};

struct CarControlFixture : CarControlDependencies
{
	CCarControl carControl;

	CarControlFixture()
		: carControl(car, input, output)
	{
	}

	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		carControl.HandleCommand();
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(CarControl_class, CarControlFixture)

	BOOST_AUTO_TEST_CASE(can_handle_main_commands)
	{
		VerifyCommandHandling("Info", "Engine is turned off\n");
		VerifyCommandHandling("EngineOn", "Engine is turned on\n");
		VerifyCommandHandling("EngineOff", "Engine is turned off\n");
		VerifyCommandHandling("SetGear 1", "\
Engine is turned off\n\
Gear can not switch to this value!\n");
		VerifyCommandHandling("SetSpeed 10", "\
Engine is turned off\n\
This speed value is not included in the valid range of the 0 gear!\n");
	}

	BOOST_AUTO_TEST_CASE(can_handle_main_commands_in_any_cases)
	{
		VerifyCommandHandling("Info", "Engine is turned off\n");
		VerifyCommandHandling("engineon", "Engine is turned on\n");
		VerifyCommandHandling("ENGINEOFF", "Engine is turned off\n");
	}

	BOOST_AUTO_TEST_CASE(should_report_if_command_is_unknown)
	{
		VerifyCommandHandling("Unknown", "Unknown command!\n");
	}

	BOOST_AUTO_TEST_CASE(should_report_if_command_can_not_be_done)
	{
		VerifyCommandHandling("EngineOff", "Engine is already off, gear is not NEUTRAL or speed is not zero!\n");
		VerifyCommandHandling("SetGear 1", "Engine is turned off\nGear can not switch to this value!\n");
		VerifyCommandHandling("SetSpeed 10", "Engine is turned off\nThis speed value is not included in the valid range of the 0 gear!\n");
		car.TurnOnEngine();
		VerifyCommandHandling("EngineOn", "Engine is already on!\n");
	}

	BOOST_AUTO_TEST_CASE(can_turn_on_engine_if_it_is_possible)
	{
		VerifyCommandHandling("EngineOn", "Engine is turned on\n");
		BOOST_CHECK(car.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(can_turn_off_engine_if_it_is_possible)
	{
		car.TurnOnEngine();
		VerifyCommandHandling("EngineOff", "Engine is turned off\n");
		BOOST_CHECK(!car.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(can_set_car_gear_if_it_is_possible)
	{
		car.TurnOnEngine();
		VerifyCommandHandling("SetGear 1", "Gear: 1\n");
		BOOST_CHECK(car.GetGear() == 1);
	}

	BOOST_AUTO_TEST_CASE(can_set_car_speed_if_it_is_possible)
	{
		car.TurnOnEngine();
		car.SetGear(-1);
		VerifyCommandHandling("SetSpeed 10", "Speed: 10\n");
		BOOST_CHECK(car.GetSpeed() == 10);
	}

	BOOST_AUTO_TEST_CASE(can_print_car_info)
	{
		VerifyCommandHandling("Info", "Engine is turned off\n");

		car.TurnOnEngine();
		car.SetGear(-1);
		car.SetSpeed(10);
		VerifyCommandHandling("Info", "\
Engine is turned on\n\
Direction: BACKWARD\n\
Gear: -1\n\
Speed: 10\n");
	}

BOOST_AUTO_TEST_SUITE_END()