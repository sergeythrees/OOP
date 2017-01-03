#pragma once

template<typename T, typename Less/* = typeid(bool operator<()))*/>
bool FindMaxEx(std::vector<T>const & arr, T & maxValue, Less const & less/* = less()*/)
{
	if (arr.empty())
	{
		return false;
	}

	const T* lastMax = &arr.front();
	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (less(*lastMax, arr[i]))
		{
			lastMax = &arr[i];
		}
	}
	maxValue = *lastMax;

	return true;
}