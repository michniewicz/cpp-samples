#include "stdafx.h"
#include "RPN.h"

RPN::RPN(void)
{
}


RPN::~RPN(void)
{
}

string RPN::GetRPN(const string& input) 
{
	if (input == "")
	    return "";

	stack <char> st;

	StringBuilder out;

	for (int i = 0; i < strlen(input.c_str()); i++)
	    switch (input.c_str()[i]) 
		{
			case '+':
			case '-':
				while (!st.empty() && (st.top() == '*' || st.top() == '/')) 
				{
					out.append(' ');
					char popped = st.top();
					out.append(popped);
					st.pop();
				}

				out.append(' ');
				st.push(input.c_str()[i]);

				break;

			case '*':
			case '/':
				out.append(' ');
				st.push(input.c_str()[i]);

	        break;

			case '(':
				st.push(input.c_str()[i]);
	        break;

			case ')':
				while (!st.empty() && st.top() != '(') 
				{
					out.append(' ');

					char popped = st.top();
					out.append(popped);

					st.pop();
				}

				st.pop();

	        break;

			default:
				out.append(input.c_str()[i]);

			break;
		}

	while (!st.empty())
	{
		char popped = st.top();

	    out.append(' ').append(popped);
		st.pop();
	}

	return out.toString();
}
