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
	CMyArrayIterator& operator++();
	CMyArrayIterator& operator--();
private:
	T* m_elementPtr;
};



template<typename T, bool isReverse>
T & CMyArrayIterator<T, isReverse>::operator*() const
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
