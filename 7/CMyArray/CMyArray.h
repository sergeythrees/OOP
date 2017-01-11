#pragma once
#include "stdafx.h"
#include <new>
#include <algorithm>

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;
	CMyArray(const CMyArray& arr);

	void Append(const T & value);
	T & GetBack();
	const T & GetBack()const;
	size_t GetSize()const;
	size_t GetCapacity()const;

	~CMyArray();
private:
	static void DeleteItems(T *begin, T *end);
	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T *srcBegin, T *srcEnd, T * const dstBegin, T * & dstEnd);
	static void DestroyItems(T *from, T *to);
	static T *RawAlloc(size_t n);
	static void RawDealloc(T *p);

private:
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
};

template <typename T>
CMyArray<T>::CMyArray(const CMyArray& arr)
{
	const auto size = arr.GetSize();
	if (size != 0)
	{
		m_begin = RawAlloc(size);
		try
		{
			CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
			m_endOfCapacity = m_end;
		}
		catch (...)
		{
			DeleteItems(m_begin, m_end);
			throw;
		}
	}
}

template <typename T>
void CMyArray<T>::Append(const T & value)
{
	if (m_end == m_endOfCapacity) // no free space
	{
		size_t newCapacity = std::max(1u, GetCapacity() * 2);

		auto newBegin = RawAlloc(newCapacity);
		T *newEnd = newBegin;
		try
		{
			CopyItems(m_begin, m_end, newBegin, newEnd);
			// Конструируем копию value по адресу newItemLocation
			new (newEnd)T(value);
			++newEnd;
		}
		catch (...)
		{
			DeleteItems(newBegin, newEnd);
			throw;
		}
		DeleteItems(m_begin, m_end);

		// Переключаемся на использование нового хранилища элементов
		m_begin = newBegin;
		m_end = newEnd;
		m_endOfCapacity = m_begin + newCapacity;
	}
	else // has free space
	{
		new (m_end) T(value);
		++m_end;
	}
}

template <typename T>
T & CMyArray<T>::GetBack()
{
	assert(GetSize() != 0u);
	return m_end[-1];
}

template <typename T>
const T & CMyArray<T>::GetBack()const
{
	assert(GetSize() != 0u);
	return m_end[-1];
}

template <typename T>
size_t CMyArray<T>::GetSize()const
{
	return m_end - m_begin;
}

template<typename T>
size_t CMyArray<T>::GetCapacity() const
{
	return m_endOfCapacity - m_begin;
}

template<typename T>
CMyArray<T>::~CMyArray()
{
	DeleteItems(m_begin, m_end);
}

template<typename T>
void CMyArray<T>::DeleteItems(T * begin, T * end)
{
	// Разрушаем старые элементы
	DestroyItems(begin, end);
	// Освобождаем область памяти для их хранения
	RawDealloc(begin);
}

template<typename T>
void CMyArray<T>::CopyItems(const T * srcBegin, T * srcEnd, T * const dstBegin, T *& dstEnd)
{
	for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
	{
		// Construct "T" at "dstEnd" as a copy of "*begin"
		new (dstEnd)T(*srcBegin);
	}
}

template<typename T>
void CMyArray<T>::DestroyItems(T * from, T * to)
{
	// dst - адрес объект, при конструирование которого было выброшено исключение
	// to - первый скорнструированный объект
	while (to != from)
	{
		--to;
		// явно вызываем деструктор для шаблонного типа T
		to->~T();
	}
}

template<typename T>
T * CMyArray<T>::RawAlloc(size_t n)
{
	size_t memSize = n * sizeof(T);
	T *p = static_cast<T*>(malloc(memSize));
	if (!p)
	{
		throw std::bad_alloc();
	}
	return p;
}

template<typename T>
void CMyArray<T>::RawDealloc(T * p)
{
	free(p);
}
