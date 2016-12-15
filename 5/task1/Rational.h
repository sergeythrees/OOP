#pragma once

class CRational final
{
public:
	CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;

	int GetDenominator() const;

	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction()const;

	CRational const operator +()  const;
	CRational const operator -()  const;
	CRational & operator +=(const CRational& b);
	CRational & operator -=(const CRational& b);
	CRational & operator *=(const CRational& b);
	CRational & operator /=(const CRational& b);
private:
	int m_numerator;
	int m_denominator;

	void Normalize();
};
unsigned GCD(unsigned a, unsigned b);
CRational const operator +(const CRational& a, const CRational& b);
CRational const operator -(const CRational& a, const CRational& b);
CRational const operator *(const CRational& a, const CRational& b);
CRational const operator /(const CRational& a, const CRational& b);
bool operator ==(const CRational& a, const CRational& b);
bool operator !=(const CRational& a, const CRational& b);
bool operator >(const CRational& a, const CRational& b);
bool operator <(const CRational& a, const CRational& b);
bool operator >=(const CRational& a, const CRational& b);
bool operator <=(const CRational& a, const CRational& b);
std::ostream & operator <<(std::ostream &stream, const CRational& rational);
std::istream & operator >>(std::istream & stream, CRational & rational);