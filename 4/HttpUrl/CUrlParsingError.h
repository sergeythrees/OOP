#pragma once
#include "stdafx.h"
#include <exception>
#include "HttpUrl.h"

class CUrlParsingError : public std::invalid_argument
{
public:
	using std::invalid_argument::invalid_argument;
};