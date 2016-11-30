#pragma once

class CRational final
{
public:
	CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;

	int GetDenominator() const;

	double ToDouble() const;

	CRational const operator +();
	CRational const operator -();
	CRational const operator +=(CRational const& b);
	CRational const operator -=(CRational const& b);
	CRational const operator *=(CRational const& b);
	CRational const operator /=(CRational const& b);
private:
	int m_numerator;
	int m_denominator;

	void Normalize();
};
unsigned GCD(unsigned a, unsigned b);
CRational const operator +(CRational const& a, CRational const& b);
CRational const operator -(CRational const& a, CRational const& b);
CRational const operator *(CRational const& a, CRational const& b);
CRational const operator /(CRational const& a, CRational const& b);
bool const operator ==(CRational const& a, CRational const& b);
bool const operator !=(CRational const& a, CRational const& b);
bool const operator >(CRational const& a, CRational const& b);
bool const operator <(CRational const& a, CRational const& b);
bool const operator >=(CRational const& a, CRational const& b);
bool const operator <=(CRational const& a, CRational const& b);
std::ostream & operator <<(std::ostream &stream, CRational const& rational);