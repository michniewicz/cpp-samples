#pragma once
#pragma warning( disable : 4996 )

#include <ostream>
using namespace std;

/// Class CharString
class CharString
{
	char* buffer;

	int length;

public:
	/// ASCII values for ToUpperCase() and ToLowerCase() methods
	enum ASCII { UPPER_YO_CYR	= -88
				, LOWER_YO_CYR	= -72
				, UPPER_A_CYR	= -64
				, LOWER_A_CYR	= -32
				, UP_LOW_DIFF	= 32
				, UPPER_A		= 65
				, UPPER_Z		= 90
				, LOWER_A		= 97
				, LOWER_Z		= 122
				};
public:

	/// Initializes a newly created CharString object with char c symbol
	CharString(char c);

	/// Initializes a newly created CharString, 
	/// it represents an empty character.
	CharString(const char* s = "");

	/// Copy constructor for CharString
	CharString(const CharString& cs);

	/// Destructor
	~CharString();

public:
	/// Returns CharString's length
	int GetLength() const
	{
		return length;
	}

	/// Returns true if string is empty, otherwise - false
	bool IsEmpty() const 
	{
		if(GetLength())
			return false;

		return true;
	}

	/// Get string (char*)
	const char* ToString() const
	{
		return buffer;
	}

	/// Set string
	void SetString(const char* s);

	/// Returns the char value at the specified index
	char CharAt(int idx);

	/// Returns the first symbol of the CharString
	char FirstSymb() const;

	/// Returns the last symbol of the CharString
	char LastSymb() const;

	/// Replace all oldChar symbols to newChar in this CharString
	void Replace(char oldChar, char newChar);

	/// Delete all symbols char c in this CharString
	void DeleteSymb(char c);	//Trim

	/// Delete all spaces in this CharString
	void DeleteSpaces();

	/// Converts all of the characters in this CharString to upper case
	CharString ToUpperCase();

	/// Converts all of the characters in this CharString to lower case
	CharString ToLowerCase();

	/// Reverse the CharString 
	CharString Reverse();

	/// Returns the CharString from the specified index to the end of CharString
	CharString Substring(int idx);

	/// Returns the CharString from the specified index and the specified length
	CharString Substring(int start, int len);

	/// Search substring of char* type in the CharString. 
	/// Returns the index within this string of the first 
	/// occurrence of the specified substring.
	/// If it does not occur as a substring, -1 is returned.
	int Search(const char* s);

	/// Search substring of CharString type in the CharString. 
	/// Returns the index within this string of the first 
	/// occurrence of the specified substring.
	/// If it does not occur as a substring, -1 is returned.
	int Search(const CharString& s);

	/// Returns the first position from the beginning of CharString, 
	/// where the specified symbol exists,
	/// otherwise it returns -1
	int FindFirst(char c) const;

	/// Returns the first position from the end of CharString, 
	/// where the specified symbol exists,
	/// otherwise it returns -1
	int FindLast(char c) const;

	/// overloaded operator = 
	CharString& operator	= (const CharString& cs);

	/// overloaded operator =
	CharString& operator	= (const char* s);

	/// overloaded operator =
	CharString& operator	= (char c);

	/// overloaded operator +
	CharString	operator	+ (const CharString& cs);

	/// overloaded operator +
	CharString	operator	+ (const char* s);

	/// overloaded operator +
	CharString operator		+ (char c);

	/// overloaded operator ==
	bool operator == (const CharString& cs);
	/// overloaded operator ==
	bool operator == (const char* str);
	/// overloaded operator ==
	bool operator == (char c);

	/// Used for the cout << (CharString)
	friend ostream& operator << (ostream& out, const CharString& s)
	{
		out << s.ToString();

		return out;
	}

	/// Used for the cin >> (CharString)
	friend istream& operator >> (istream& in, CharString& s)
	{
		char str[256] = {0};
		cin >> str;

		s.SetString(str);

		return in;
	}
private:
	/// Memory allocation and copying
	void New(const char* s);

	/// Frees memory
	void Delete();

	int CheckIdx(int idx);
};