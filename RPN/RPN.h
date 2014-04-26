#pragma once

#include "StringBuilder.h"

class RPN
{

public:
	RPN(void);

	~RPN(void);

	static string GetRPN(const string& input);
};

