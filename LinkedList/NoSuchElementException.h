#pragma once

#include "Exception.h"


class NoSuchElementException : public Exception
{
	CharString msg;
public:
	NoSuchElementException(const char* m);

	~NoSuchElementException(void);

	CharString What();
};

