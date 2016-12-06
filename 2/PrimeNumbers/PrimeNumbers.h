#pragma once
#include "stdafx.h"

const int MAX_UPPER_BOUND = 100000000;
const int MIN_PRIME_NUMBER = 2;

std::set<int> GeneratePrimeNumbersSet(int upperBound);
bool IsValidUpperBound(int upperBound);