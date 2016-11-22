#include "stdafx.h"
#include "../Car/CarControl.h"
#include "../Car/Car.h"
#include <sstream>
#include <boost/optional.hpp>

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
		BOOST_CHECK(carControl.HandleCommand());
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Car_Control, CarControlFixture)

BOOST_AUTO_TEST_CASE(can_handle_EngineOn_command)
{
	VerifyCommandHandling("EngineOn", "Engine is turned on\n");
}

BOOST_AUTO_TEST_CASE(can_turn_off_engine_which_is_on)
{
	car.TurnOnEngine();
	VerifyCommandHandling("EngineOff", "Engine is turned off\n");
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


BOOST_AUTO_TEST_CASE(can_set_a_valid_gear_when_engine_is_turned_on)
{
car.TurnOnEngine();
VerifyCommandHandling("SetGear 1", "Gear: 1\n");
}


BOOST_AUTO_TEST_CASE(cant_set_speed_when_engine_is_turned_off)
{
VerifyCommandHandling("SetSpeed 10", "\
Engine is turned off\n\
This speed value is not included in the valid range of the 0 gear!\n");
}

/*
// Раскомментируйте тест, проверяющий работу команды SelectChannel
//	попытке при выбрать недоступный номер канала у включенного телевизора
// Убедитесь, что он не проходит (т.к. в CRemoteControl отсутствует требуемый функционал)
// Доработайте простейшим образом класс CRemoteControl, чтобы этот тест и предыдущие проходили
// При необходимости выполните рефакторинг кода, сохраняя работоспособность тестов
BOOST_AUTO_TEST_CASE(cant_select_an_invalid_channel_when_tv_is_on)
{
tv.TurnOn();
tv.SelectChannel(42);
VerifyCommandHandling("SelectChannel 100", 42, "Invalid channel\n");
VerifyCommandHandling("SelectChannel 0", 42, "Invalid channel\n");
}
*/

// Напишите тесты для недостающего функционала класса CRemoteControl (если нужно)
//	и для дополнительных заданий на бонусные баллы (если нужно)
// После написания каждого теста убедитесь, что он не проходит.
// Доработайте простейшим образом класс CRemoteControl, чтобы этот тест и предыдущие проходили
// При необходимости выполните рефакторинг кода, сохраняя работоспособность тестов
// При необходимости используйте вложенные тесты (как использующие fixture, так и нет)
// Имена тестам и test suite-ам давайте такие, чтобы выводимая в output иерархия
//	тестов читалась как спецификация на английском языке, описывающая поведение remote control-а

BOOST_AUTO_TEST_SUITE_END()