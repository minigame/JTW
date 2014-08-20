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

std::string DataConversion::convertPoint2str(cocos2d::Point p)
{
	std::string msg;
	char buffer[10];

	msg += "(";
	itoa(p.x, buffer, 10);
	msg += buffer;
	msg += ", ";
	itoa(p.y, buffer, 10);
	msg += buffer;
	msg += ")";

	return msg;
}
