#pragma once

#include "CharString.h"

class Exception
{

public:
	Exception(void);

	~Exception(void);

	virtual CharString What()=0;
};

