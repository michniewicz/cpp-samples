#include "StdAfx.h"
#include "StringBuilder.h"


StringBuilder::StringBuilder(void)
{
}


StringBuilder::~StringBuilder(void)
{
}

StringBuilder& StringBuilder::append(const string & str) 
{
	buffer.append(str);

    return *this;
}

StringBuilder& StringBuilder::append(char c) 
{

	char tmp[2] = {0};
	tmp[0] = c;
	tmp[1] = '\0';

	string str = tmp;

    return append(str);
}