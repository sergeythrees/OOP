﻿// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../task1/Rational.h"

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}



/*
  Рациональное число:
	равно нулю по умолчанию (0/1)
	может быть созданно из целого в формате (n / 1)
	может быть задано с указанием числителя и знаменателя
	хранится в нормализованном виде
	*/

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}




//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
// Возвращает отношение числителя и знаменателя в виде числа double
// Пример использования:
//	CRational r(3, 5)
//	cout << r.ToDouble(); // Должно вывести 0.6
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(ToDouble_function)
	BOOST_AUTO_TEST_CASE(should_convert_the_rational_number_to_double)
	{
		CRational rational(3, 5);
		BOOST_CHECK_CLOSE(rational.ToDouble(), 0.6, 0.01);
	}
BOOST_AUTO_TEST_SUITE_END()



//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
// Указание: см. материалы к лекции
// Пример использования:
//	const CRational r1(3, 5);
//	CRational r2 = -r1; // r2 должно стать -3/5
//	assert(r2.GetNumerator(), -3);
//	assert(r2.GetDenominator(), 5);
//	CRational r3 = +r2; // r3 также равно -3/5
//	assert(r3.GetNumerator(), -3);
//	assert(r3.GetDenominator(), 5);
// Унарный минус возвращает раицональное число без знака
// Унарный плюс возвращает рациональное число, равное текущему
// Реализация не должна допускать операции вроде:
//  -someRational = someOtherRational;
//	+someRational = someOtherRational;
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(unary_operator_minus)
	BOOST_AUTO_TEST_CASE(should_return_the_rational_number_with_the_opposite_sign)
	{
		VerifyRational(-CRational(3, 5), -3, 5);
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(unary_operator_plus)
BOOST_AUTO_TEST_CASE(should_return_not_changed_rational_number)
{
	VerifyRational(+CRational(3, 5), 3, 5);
	VerifyRational(+CRational(-3, 5), -3, 5);
}
BOOST_AUTO_TEST_SUITE_END()



//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
// Возвращает результат сложения двух рациональных чисел, 
//	рационального числа с целым, целого числа с рациональным.
//	(1/2) + (1/6) = (2/3)
//	(1/2) + 1     = (3/2)
//	1 + (1/2)     = (3/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(binary_operator_plus)
	BOOST_AUTO_TEST_CASE(should_return_the_sum_of_two_rational_numbers)
	{
		VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);
	}
	BOOST_AUTO_TEST_CASE(should_return_the_sum_of_rational_number_and_integer)
	{
		VerifyRational(CRational(1, 2) + 1, 3, 2);
	}
	BOOST_AUTO_TEST_CASE(should_return_the_sum_of_integer_and_rational_number)
	{
		VerifyRational(1 + CRational(1, 2), 3, 2);
	}
BOOST_AUTO_TEST_SUITE_END()



//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
// Возвращает разность двух рациональных чисел, 
//	рационального числа и целого, либо целого числа и рационального:
//	(1/2) - (1/6) = (1/3)
//	(1/2) - 1     = (-1/2)
//	1 - (1/2)     = (1/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(binary_operator_minus)
BOOST_AUTO_TEST_CASE(should_return_the_complement_of_two_rational_numbers)
{
	VerifyRational(CRational(1, 2) - CRational(1, 6), 1, 3);
}
BOOST_AUTO_TEST_CASE(should_return_the_complement_of_rational_number_and_integer)
{
	VerifyRational(CRational(1, 2) - 1, -1, 2);
}
BOOST_AUTO_TEST_CASE(should_return_the_complement_of_integer_and_rational_number)
{
	VerifyRational(1 - CRational(1, 2), 1, 2);
}
BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
// Выполняет увеличение рационального числа на величину второго рационального,
//	либо целого числа:
//	(1/2) += (1/6)  → (2/3)
//	(1/2) += 1      → (3/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(plus_equal_operator)
BOOST_AUTO_TEST_CASE(should_add_second_rational_number_to_first_rational_number)
{
	VerifyRational(CRational(1, 2) += CRational(1, 6), 2, 3);
}
BOOST_AUTO_TEST_CASE(should_add_integer_to_first_rational_number)
{
	VerifyRational(CRational(1, 2) += 1, 3, 2);
}
BOOST_AUTO_TEST_SUITE_END()




//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
// (1/2) -= (1/6)  → (1/3)
// (1/2) -= 1      → (-1/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(minus_equal_operator)
BOOST_AUTO_TEST_CASE(should_subtract_second_rational_number_from_first_rational_number)
{
	VerifyRational(CRational(1, 2) -= CRational(1, 6), 1, 3);
}
BOOST_AUTO_TEST_CASE(should_subtract_integer_from_first_rational_number)
{
	VerifyRational(CRational(1, 2) -= 1, -1, 2);
}
BOOST_AUTO_TEST_SUITE_END()



//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
// Возвращает результат произведения рациональных чисел, 
//	рационального и целого, либо целого и рационального :
//	(1/2) * (2/3) = (1/3)
//	(1/2) * (-3)  = (-3/2)
//	7 * (2/3)     = (14/3)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(multiplicaton_operator)
BOOST_AUTO_TEST_CASE(should_return_the_result_of_multiplicaton_two_rational_numbers)
{
	VerifyRational(CRational(1, 2) * CRational(2, 3), 1, 3);
}
BOOST_AUTO_TEST_CASE(should_return_the_result_of_multiplicaton_rational_number_and_integer)
{
	VerifyRational(CRational(1, 2) * -3, -3, 2);
}
BOOST_AUTO_TEST_CASE(should_return_the_result_of_multiplicaton_integer_and_rational_number)
{
	VerifyRational(7 * CRational(2, 3), 14, 3);
}
BOOST_AUTO_TEST_SUITE_END()




//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
// Возвращает частное двух рациональных чисел, 
//	рационального и целого, целого и рационального :
//	(1/2) ⁄ (2/3) = (3/4)
//	(1/2) ⁄ 5     = (1/10)
//	7 ⁄ (2/3)     = (21/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(division_operator)
BOOST_AUTO_TEST_CASE(should_return_the_result_of_division_two_rational_numbers)
{
	VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4);
}
BOOST_AUTO_TEST_CASE(should_return_the_result_of_division_rational_number_and_integer)
{
	VerifyRational(CRational(1, 2) / 5, 1, 10);
}
BOOST_AUTO_TEST_CASE(should_return_the_result_of_division_integer_and_rational_number)
{
	VerifyRational(7 / CRational(2, 3), 21, 2);
}
BOOST_AUTO_TEST_SUITE_END()




//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(multiple_equal_operator)
BOOST_AUTO_TEST_CASE(should_multiply_the_first_rational_number_by_second_rational_number)
{
	VerifyRational(CRational(1, 2) *= CRational(2, 3), 1, 3);
}
BOOST_AUTO_TEST_CASE(should_multiply_the_rational_number_by_integer)
{
	VerifyRational(CRational(1, 2) *= 3, 3, 2);
}
BOOST_AUTO_TEST_SUITE_END()




//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
// Делит первое рациональное число на другое рациональное, 
//	либо целое:
//	(1/2) /= (2/3) → (3/4)
//	(3/4) /= (3/8) → (2/1)
//	(1/2) /= 3     → (1/6)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(division_and_equal_operator)
BOOST_AUTO_TEST_CASE(should_divide_the_first_rational_number_by_second_rational_number)
{
	VerifyRational(CRational(1, 2) /= CRational(2, 3), 3, 4);
}
BOOST_AUTO_TEST_CASE(should_divide_the_rational_number_by_integer)
{
	VerifyRational(CRational(1, 2) /= 3, 1, 6);
}
BOOST_AUTO_TEST_SUITE_END()




//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
// Проверяют равенство (и неравенство) двух рациональных чисел, 
//	целого и рационального, рационального и целого:
//	(1/2) == (1/2) → true
//	(4/1) == 4     → true
//	3 == (3/1)     → true
//	(1/2) != (2/3) → true
//	(1/2) != 7     → true
//	3 != (2/3)     → true
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(bool_operator_equal)
	BOOST_AUTO_TEST_CASE(return_true_if_two_rational_numbers_are_equal)
	{
		BOOST_CHECK(CRational(1, 2) == CRational(1, 2));
	}
	BOOST_AUTO_TEST_CASE(return_true_if_rational_number_and_integer_are_equal)
	{
		BOOST_CHECK(CRational(4, 1) == 4);
	}
	BOOST_AUTO_TEST_CASE(return_true_if_integer_and_rational_number_are_equal)
	{
		BOOST_CHECK(3 == CRational(3, 1));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(bool_operator_not_equal)
	BOOST_AUTO_TEST_CASE(return_true_if_two_rational_numbers_are_not_equal)
	{
		BOOST_CHECK(CRational(1, 2) != CRational(2, 3));
	}
	BOOST_AUTO_TEST_CASE(return_true_if_rational_number_and_integer_are_equal)
	{
		BOOST_CHECK(CRational(1, 2) != 7);
		BOOST_CHECK(!(CRational(7, 1) != 7));
	}
	BOOST_AUTO_TEST_CASE(return_true_if_integer_and_rational_number_are_equal)
	{
		BOOST_CHECK(3 != CRational(2, 3));
		BOOST_CHECK(!(3 != CRational(3, 1)));
	}
BOOST_AUTO_TEST_SUITE_END()



//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
// Сравнивают два рациональных числа, рациональное с целым, 
//	целое с рациональным:
//	(1/2) >= (1/3) → true
//	(1/2) <= (1/3) → false
//	(3/1) > 2      → true
//	(1/2) < 7      → true
//	3 <= (7/2)     → true
//	3 >= (8/2)     → false
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(bool_operator_greater)
	BOOST_AUTO_TEST_CASE(returns_true_if_first_rational_number_is_greater_than_second)
	{
		BOOST_CHECK(CRational(1, 2) > CRational(1, 3));
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_rational_number_is_greater_than_integer)
	{
		BOOST_CHECK(CRational(4, 1) > 3);
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_integer_is_greater_than_rational_number)
	{
		BOOST_CHECK(1 > CRational(1, 2));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(bool_operator_less)
	BOOST_AUTO_TEST_CASE(returns_true_if_first_rational_number_is_less_than_second)
	{
		BOOST_CHECK(CRational(1, 3) < CRational(1, 2));
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_rational_number_is_less_than_integer)
	{
		BOOST_CHECK(CRational(1, 2) < 1);
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_integer_is_less_than_rational_number)
	{
		BOOST_CHECK(1 < CRational(3, 2));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(bool_operator_greater_or_equal)
	BOOST_AUTO_TEST_CASE(returns_true_if_first_rational_number_is_greater_than_second_or_they_are_equal)
	{
		BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
		BOOST_CHECK(CRational(1, 2) >= CRational(1, 2));
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_rational_number_is_greater_than_integer_or_they_are_equal)
	{
		BOOST_CHECK(CRational(4, 1) >= 3);
		BOOST_CHECK(CRational(3, 1) >= 3);
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_integer_is_greater_than_rational_number_or_they_are_equal)
	{
		BOOST_CHECK(1 >= CRational(1, 2));
		BOOST_CHECK(2 >= CRational(2, 1));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(bool_operator_less_or_equal)
	BOOST_AUTO_TEST_CASE(returns_true_if_first_rational_number_is_less_than_second_or_they_are_equal)
	{
		BOOST_CHECK(CRational(1, 3) <= CRational(1, 2));
		BOOST_CHECK(CRational(1, 3) <= CRational(1, 3));
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_rational_number_is_less_than_integer_or_they_are_equal)
	{
		BOOST_CHECK(CRational(1, 2) <= 1);
		BOOST_CHECK(CRational(2, 1) <= 2);
	}
	BOOST_AUTO_TEST_CASE(returns_true_if_integer_is_less_than_rational_number_or_they_are_equal)
	{
		BOOST_CHECK(1 <= CRational(3, 2));
		BOOST_CHECK(2 <= CRational(2, 1));
	}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(output_operator)
	BOOST_AUTO_TEST_CASE(should_output_the_rational_number_in_the_stream)
	{
		std::stringstream output = std::stringstream();
		output << CRational(7,15);
		BOOST_CHECK_EQUAL(output.str(), "7/15");
	}

BOOST_AUTO_TEST_SUITE_END()




//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////



BOOST_AUTO_TEST_SUITE_END()
