#include "StdAfx.h"
#include "NoSuchElementException.h"


NoSuchElementException::NoSuchElementException(const char* m)
{
	msg	= m;
}


NoSuchElementException::~NoSuchElementException(void)
{
}

CharString NoSuchElementException::What()
{
	return msg;
}