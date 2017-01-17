#pragma once
#include "stdafx.h"
#include "CMyArray.h"

template<typename T, bool isReverse>
class CMyArrayIterator: public std::iterator<std::bidirectional_iterator_tag, T> 
{
	template<typename T>  friend class CMyArray;
public:
	CMyArrayIterator() = default;
	CMyArrayIterator(T * elementPtr) :m_elementPtr(elementPtr) {}

	T& operator *()const;
	T& operator ->()const;
	CMyArrayIterator& operator++();
	CMyArrayIterator& operator--();
	CMyArrayIterator& operator++(int);
	CMyArrayIterator& operator--(int);
	bool operator ==(const CMyArrayIterator& it);
	bool operator !=(const CMyArrayIterator& it);
private:
	T* m_elementPtr;
};

template<typename T, bool isReverse>
T & CMyArrayIterator<T, isReverse>::operator*() const
{
	return *m_elementPtr;
}

template<typename T, bool isReverse>
T & CMyArrayIterator<T, isReverse>::operator->() const
{
	return *m_elementPtr;
}

template<typename T, bool isReverse>
CMyArrayIterator<T, isReverse> & CMyArrayIterator<T, isReverse>::operator++()
{
	isReverse ? --m_elementPtr : ++m_elementPtr;
	return *this;
}

template<typename T, bool isReverse>
CMyArrayIterator<T, isReverse> & CMyArrayIterator<T, isReverse>::operator--()
{
	isReverse ? ++m_elementPtr : --m_elementPtr;
	return *this;
}

template<typename T, bool isReverse>
CMyArrayIterator<T, isReverse> & CMyArrayIterator<T, isReverse>::operator++(int)
{
	if (isReverse)
	{
		return{ m_elementPtr-- };
	}
	return{ m_elementPtr++ };
}

template<typename T, bool isReverse>
CMyArrayIterator<T, isReverse> & CMyArrayIterator<T, isReverse>::operator--(int)
{
	if (isReverse)
	{
		return{ m_elementPtr++ };
	}
	return{ m_elementPtr-- };
}

template<typename T, bool isReverse>
bool CMyArrayIterator<T, isReverse>::operator==(const CMyArrayIterator & it)
{
	return m_elementPtr == it.m_elementPtr;
}

template<typename T, bool isReverse>
bool CMyArrayIterator<T, isReverse>::operator!=(const CMyArrayIterator & it)
{
	return !(*this == it);
}