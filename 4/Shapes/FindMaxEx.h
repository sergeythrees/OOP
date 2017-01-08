#pragma once

template<typename T, typename Less>
T* FindMaxEx(std::vector<T> & arr, Less const & less)
{
	if (arr.empty())
	{
		return nullptr;
	}

	T* lastMax = &arr.front();
	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (less(*lastMax, arr[i]))
		{
			lastMax = &arr[i];
		}
	}

	return lastMax;
}