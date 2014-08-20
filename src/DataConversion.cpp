#include "DataConversion.h"

#if defined(__OSX__)
// 注意，OSX上没有itoa()函数，这里使用sprintf来模拟
char *  itoa ( int value, char * str, int base )
{
    if (base == 10) {
        sprintf(str, "%d", value);
    }
    else if (base == 16) {
        sprintf(str, "%x", value);
    }
    else if (base == 8) {
        sprintf(str, "%o", value);
    }
    return str;
}
#endif

#if defined(ANDROID)
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
