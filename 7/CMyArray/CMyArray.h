#pragma once
#include "stdafx.h"
#include "CMyIterator.h"
#include <new>

template <typename T>
class CMyArray
{
	template<typename T, bool isReverse>  friend class CMyIterator;
public:
	typedef CMyIterator<T, false> iterator;
	typedef CMyIterator<const T, false> const_iterator;
	typedef CMyIterator<T, true> reverse_iterator;
	typedef CMyIterator<const T, true> const_reverse_iterator;

	CMyArray() = default;
	CMyArray(const CMyArray& arr);
	CMyArray(CMyArray&& arr);

	void Append(const T & value);
	T & GetBack();
	const T & GetBack()const;
	size_t GetSize()const;
	size_t GetCapacity()const;
	void Resize(size_t newSize);
	void Clear();
	T & operator [](size_t index);
	const T & operator [](size_t index) const;
	CMyArray& operator =(const CMyArray& arr);
	CMyArray& operator =(CMyArray&& arr);
	
	const_iterator begin() const
		{	return const_iterator(m_begin);}
	const_iterator end() const
		{	return const_iterator(m_end);}
	iterator begin()
		{	return iterator(m_begin);}
	iterator end()
		{	return iterator(m_end);}
	const_reverse_iterator rbegin() const
		{	return const_reverse_iterator(m_end -1);}
	const_reverse_iterator rend() const
		{	return const_reverse_iterator(m_begin-1);}
	reverse_iterator rbegin()
		{	return reverse_iterator(m_end-1);}
	reverse_iterator rend()
		{	return reverse_iterator(m_begin-1);}

	~CMyArray();
private:
	static void DeleteItems(T *begin, T *end);
	static void CopyItems(const T *srcBegin, T *srcEnd, T * const dstBegin, T * & dstEnd);
	static void DestroyItems(T *from, T *to);
	static T *RawAlloc(size_t n);
	static void RawDealloc(T *p);

private:
	T *m_rbegin = nullptr;
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
		catch (...) {
			DeleteItems(m_begin, m_end);
			throw; }
	}
}

template<typename T>
CMyArray<T>::CMyArray(CMyArray && arr)
	:m_begin(arr.m_begin),
	m_end(arr.m_end),
	m_endOfCapacity(arr.m_endOfCapacity)
{
	arr.m_begin = nullptr;
	arr.m_end = nullptr;
	arr.m_endOfCapacity = nullptr;
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
			// ������������ ����� value �� ������ newItemLocation
			new (newEnd)T(value);
			++newEnd;
		}
		catch (...) {
			DeleteItems(newBegin, newEnd);
			throw; }
		DeleteItems(m_begin, m_end);

		// ������������� �� ������������� ������ ��������� ���������
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
void CMyArray<T>::Resize(size_t newSize)
{
	size_t currentSize = GetSize();
	size_t oldSize = GetSize();
	auto endBackup = m_end;
	if (newSize < currentSize)
	{
		DestroyItems(m_begin + newSize, m_end);
		m_end = m_begin + newSize;
	}
	while (newSize > currentSize)
	{
		try
		{
			Append(T());
		}
		catch (...) {
			if (currentSize > oldSize)
			{
				DeleteItems(endBackup, endBackup + (currentSize - oldSize));
				m_end = endBackup;
			}
			
			throw; }
		currentSize++;
	}
}

template<typename T>
void CMyArray<T>::Clear()
{
	DeleteItems(m_begin, m_end);
	m_begin = nullptr;
	m_end = nullptr;
	m_endOfCapacity = nullptr;
}

template<typename T>
T & CMyArray<T>::operator[](size_t index)
{
	if (index >= GetSize())
		throw std::out_of_range("Index exceeds array size!");

	return *(m_begin + index);
}

template<typename T>
const T & CMyArray<T>::operator[](size_t index) const
{
	if (index >= GetSize())
		throw std::out_of_range("Index exceeds array size!");

	return *(m_begin + index);
}

template<typename T>
CMyArray<T>& CMyArray<T>::operator=(const CMyArray<T>& arr)
{
	if (&arr != this)
	{
		*this = move(CMyArray<T>(arr));
	}
	
	return *this;
}

template<typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray<T>&& arr)
{
	if (&arr != this)
	{
		Clear();

		m_begin = arr.m_begin;
		m_end = arr.m_end;
		m_endOfCapacity = arr.m_endOfCapacity;

		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	return *this;
}


template<typename T>
CMyArray<T>::~CMyArray()
{
	DeleteItems(m_begin, m_end);
}

template<typename T>
void CMyArray<T>::DeleteItems(T * begin, T * end)
{
	// ��������� ������ ��������
	DestroyItems(begin, end);
	// ����������� ������� ������ ��� �� ��������
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
	// dst - ����� ������, ��� ��������������� �������� ���� ��������� ����������
	// to - ������ ������������������ ������
	while (to != from)
	{
		--to;
		// ���� �������� ���������� ��� ���������� ���� T
		to->~T();
	}
}

template<typename T>
T * CMyArray<T>::RawAlloc(size_t n)
{
	size_t memSize = n * sizeof(T);
	T *p = static_cast<T*>(malloc(memSize));
	return p;
}

template<typename T>
void CMyArray<T>::RawDealloc(T * p)
{
	free(p);
}

