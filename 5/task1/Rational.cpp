﻿#include "stdafx.h"
#include "Rational.h"
#include <string>
#include <utility>
#include <stdexcept>


CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator) / m_denominator;
}

std::pair<int, CRational> CRational::ToCompoundFraction()const
{
	int integer = m_numerator / m_denominator;
	int numerator = m_numerator - integer * m_denominator;
	return{ integer, CRational(numerator, m_denominator) };
}

CRational const CRational::operator +() const
{
	return *this;
}

CRational const CRational::operator -() const
{
	return CRational(-(*this).m_numerator, (*this).m_denominator);
}

CRational const operator +(const CRational& a, const CRational& b)
{

	int numerator = a.GetNumerator() * b.GetDenominator() +
		b.GetNumerator() * a.GetDenominator();
	int denominator = a.GetDenominator() * b.GetDenominator();
	return CRational(numerator, denominator);
}

CRational const operator -(const CRational& a, const CRational& b)
{

	int numerator = a.GetNumerator() * b.GetDenominator() -
		b.GetNumerator() * a.GetDenominator();
	int denominator = a.GetDenominator() * b.GetDenominator();
	return CRational(numerator, denominator);
}

CRational & CRational::operator +=(const CRational& b)
{
	*this = *this + b;
	return *this;
}

CRational & CRational::operator -=(const CRational& b)
{
	*this = *this - b;
	return *this;
}

CRational const operator *(const CRational& a, const CRational& b) 
{
	int numerator = a.GetNumerator() * b.GetNumerator();
	int denominator = a.GetDenominator() * b.GetDenominator();
	return CRational(numerator, denominator);
}

CRational const operator /(const CRational& a, const CRational& b)
{
	int numerator = a.GetNumerator() * b.GetDenominator();
	int denominator = a.GetDenominator() * b.GetNumerator();
	return CRational(numerator, denominator);
}

CRational & CRational::operator *=(const CRational& b)
{
	*this = *this * b;
	return *this;
}

CRational & CRational::operator /=(const CRational& b)
{
	*this = *this / b;
	return *this;
}

bool operator ==(const CRational& a, const CRational& b)
{
	return ((a.GetNumerator() == b.GetNumerator()) && (a.GetDenominator() == b.GetDenominator()));
}

bool operator !=(const CRational& a, const CRational& b)
{
	return !(a==b);
}

bool operator >(const CRational& a, const CRational& b)
{
	int aNumerator = a.GetNumerator() * b.GetDenominator();
	int bNumerator = b.GetNumerator() * a.GetDenominator();
	return (aNumerator > bNumerator);
}

bool operator <(const CRational& a, const CRational& b)
{
	int aNumerator = a.GetNumerator() * b.GetDenominator();
	int bNumerator = b.GetNumerator() * a.GetDenominator();
	return (aNumerator < bNumerator);
}

bool operator >=(const CRational& a, const CRational& b)
{
	return !(a < b);
}

bool operator <=(const CRational& a, const CRational& b)
{
	return !(a > b);
}

std::ostream & operator <<(std::ostream &stream, const CRational& rational)
{
	stream << rational.GetNumerator() << "/" << rational.GetDenominator();
	return stream;
}

std::istream & operator >> (std::istream & stream, CRational & rational)
{
	int numerator;
	int denominator = 0;

	if (
		(stream >> numerator) && (stream.get() == '/') &&
		(stream >> denominator)
		)
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		stream.setstate(std::ios_base::failbit);
	}

	return stream;
}