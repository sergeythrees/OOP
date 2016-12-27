#pragma once

template<typename T, typename Less>
bool FindMaxEx(std::vector<T>const & arr, T & maxValue, Less const & less)
{
	if (arr.empty())
	{
		return false;
	}
	const T* lastMax = &arr[0];
	for (size_t i=0; i < arr.size(); ++i)
	{
		if (less(*lastMax, arr[i]))
		{
			lastMax = &arr[i];
		}
	}
	maxValue = *lastMax;
	return true;
}