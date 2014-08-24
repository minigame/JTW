#include "DataConversion.h"

#if defined(ANDROID) or defined(__OSX__)
char *itoa(int val, char *buf, unsigned radix)
{
	char   *p;
	char   *firstdig;
	char   temp;
	unsigned   digval;
	p = buf;
	if (val < 0)
	{
		*p++ = '-';
		val = (unsigned long)(-(long)val);
	}
	firstdig = p;
	do{
		digval = (unsigned)(val % radix);
		val /= radix;

		if (digval > 9)
			*p++ = (char)(digval - 10 + 'a');
		else
			*p++ = (char)(digval + '0');
	} while (val > 0);

	*p-- = '\0';
	do{
		temp = *p;
		*p = *firstdig;
		*firstdig = temp;
		--p;
		++firstdig;
	} while (firstdig < p);
	return buf;
}
#endif // ANDROID

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
