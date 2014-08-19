#include "DataConversion.h"


DataConversion::DataConversion()
{
}


DataConversion::~DataConversion()
{
	
}


float DataConversion::convertStr2float(const std::string& str)
{
	return atof(str.c_str());
}