#pragma once

class StringBuilder 
{
    string buffer;

public:
	StringBuilder();

	~StringBuilder();

	/// Appends string to buffer
    StringBuilder& append(const string & str);

	/// Appends char with value c to buffer
	StringBuilder& append(char c);

	/// Returns value of the buffer
    const string& toString() { return buffer; }
};
