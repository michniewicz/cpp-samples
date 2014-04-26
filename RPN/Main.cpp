#include "stdafx.h"

#include "RPN.h"

int main() 
{
	string ar = "1+3-4*(4-5)/3+90-(34-9+3)";

	string out = RPN::GetRPN(ar);
	cout << out;


	return 0;
}