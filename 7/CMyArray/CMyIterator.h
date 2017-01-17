#pragma once
#include "stdafx.h"
#include "CMyArray.h"

template<typename T, bool isReverse>
class CMyIterator: public std::iterator<std::bidirectional_iterator_tag, T> 
{
public:
	CMyIterator()
		:m_isReverse(isReverse) {}
	CMyIterator(T * elementPtr) 
		:m_elementPtr(elementPtr), 
		m_isReverse(isReverse) {}

	T& operator *()const;
	T* operator ->()const;
	CMyIterator& operator++();
	CMyIterator& operator--();
	const CMyIterator operator++(int);
	const CMyIterator operator--(int);
	bool operator ==(const CMyIterator& it);
	bool operator !=(const CMyIterator& it);
private:
	T* m_elementPtr;
	bool m_isReverse;
};

template<typename T, bool isReverse>
T & CMyIterator<T, isReverse>::operator*() const
{
	return *m_elementPtr;
}

template<typename T, bool isReverse>
T * CMyIterator<T, isReverse>::operator->() const
{
	return m_elementPtr;
}

template<typename T, bool isReverse>
CMyIterator<T, isReverse> & CMyIterator<T, isReverse>::operator++()
{
	isReverse ? --m_elementPtr : ++m_elementPtr;
	return *this;
}

template<typename T, bool isReverse>
CMyIterator<T, isReverse> & CMyIterator<T, isReverse>::operator--()
{
	isReverse ? ++m_elementPtr : --m_elementPtr;
	return *this;
}

template<typename T, bool isReverse>
const CMyIterator<T, isReverse> CMyIterator<T, isReverse>::operator++(int)
{
	auto copy(*this);
	isReverse ? --m_elementPtr : ++m_elementPtr;
	return	copy;
}

template<typename T, bool isReverse>
const CMyIterator<T, isReverse> CMyIterator<T, isReverse>::operator--(int)
{
	auto copy(*this);
	isReverse ? ++m_elementPtr : --m_elementPtr;
	return	copy;
}

template<typename T, bool isReverse>
bool CMyIterator<T, isReverse>::operator==(const CMyIterator & it)
{
	return m_elementPtr == it.m_elementPtr;
}

template<typename T, bool isReverse>
bool CMyIterator<T, isReverse>::operator!=(const CMyIterator & it)
{
	return !(*this == it);
}