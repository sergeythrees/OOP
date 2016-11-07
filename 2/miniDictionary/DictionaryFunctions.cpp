#include "stdafx.h"
#include "DictionaryFunctions.h"
#include <fstream>
#include <iostream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>

void GetDictionaryFromFile(std::fstream &file, Dictionary &dictionary)
{
	if (file.is_open())
	{
		boost::archive::binary_iarchive bia(file);
		bia >> dictionary;
		file.close();
	}
}
void SaveDictionaryToFile(std::fstream &file, Dictionary &dictionary)
{
	if (file.is_open())
	{
		boost::archive::binary_oarchive boa(file);
		boa << dictionary;
		file.close();
	}
}