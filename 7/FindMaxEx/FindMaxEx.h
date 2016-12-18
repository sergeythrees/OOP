#pragma once

template<typename T, typename Less>
bool FindMaxEx(std::vector<T>const & arr, T & maxValue, Less const & less)
{
	if (arr.empty())
	{
		return false;
	}
	T lastMax = arr.front();
	for (auto current : arr)
	{
		if (less(lastMax, current))
		{
			lastMax = current;
		}
	}
	maxValue = lastMax;
	return true;
}