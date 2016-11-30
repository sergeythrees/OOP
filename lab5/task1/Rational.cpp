#include "stdafx.h"
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

CRational const CRational::operator +() 
{
	return *this;
}

CRational const CRational::operator -()
{
	(*this).m_numerator = -(*this).m_numerator;
	return *this;
}

CRational const operator +(CRational const& a, CRational const& b)
{

	int numerator = a.GetNumerator() * b.GetDenominator() +
		b.GetNumerator() * a.GetDenominator();
	int denominator = a.GetDenominator() * b.GetDenominator();
	return CRational(numerator, denominator);
}

CRational const operator -(CRational const& a, CRational const& b)
{

	int numerator = a.GetNumerator() * b.GetDenominator() -
		b.GetNumerator() * a.GetDenominator();
	int denominator = a.GetDenominator() * b.GetDenominator();
	return CRational(numerator, denominator);
}

CRational const CRational::operator +=(CRational const& b)
{
	*this = *this + b;
	return *this;
}

CRational const CRational::operator -=(CRational const& b)
{
	*this = *this - b;
	return *this;
}

CRational const operator *(CRational const& a, CRational const& b) 
{
	int numerator = a.GetNumerator() * b.GetNumerator();
	int denominator = a.GetDenominator() * b.GetDenominator();
	return CRational(numerator, denominator);
}

CRational const operator /(CRational const& a, CRational const& b)
{
	int numerator = a.GetNumerator() * b.GetDenominator();
	int denominator = a.GetDenominator() * b.GetNumerator();
	return CRational(numerator, denominator);
}

CRational const CRational::operator *=(CRational const& b)
{
	*this = *this * b;
	return *this;
}

CRational const CRational::operator /=(CRational const& b)
{
	*this = *this / b;
	return *this;
}

bool const operator ==(CRational const& a, CRational const& b)
{
	return ((a.GetNumerator() == b.GetNumerator()) && (a.GetDenominator() == b.GetDenominator()));
}

bool const operator !=(CRational const& a, CRational const& b)
{
	return !(a==b);
}

bool const operator >(CRational const& a, CRational const& b)
{
	int aNumerator = a.GetNumerator() * b.GetDenominator();
	int bNumerator = b.GetNumerator() * a.GetDenominator();
	return (aNumerator > bNumerator);
}

bool const operator <(CRational const& a, CRational const& b)
{
	int aNumerator = a.GetNumerator() * b.GetDenominator();
	int bNumerator = b.GetNumerator() * a.GetDenominator();
	return (aNumerator < bNumerator);
}

bool const operator >=(CRational const& a, CRational const& b)
{
	return ((a > b) || (a == b));
}

bool const operator <=(CRational const& a, CRational const& b)
{
	return ((a < b) || (a == b));
}

std::ostream & operator <<(std::ostream &stream, CRational const& rational)
{
	stream << rational.GetNumerator() << "/" << rational.GetDenominator();
	return stream;
}

