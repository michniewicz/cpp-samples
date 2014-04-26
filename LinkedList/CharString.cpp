#include "StdAfx.h"
#include "CharString.h"


CharString::CharString(char c)
{
	char tmp[2] = {0};
	tmp[0] = c;

	New(tmp);
}

CharString::CharString(const char* s)
{
	New(s);
}

CharString::CharString(const CharString& cs)
{
	New(cs.buffer);
}


CharString::~CharString()
{
	Delete();
}

void CharString::SetString(const char* s)
{
	if(buffer)
		Delete();

	New(s);
}

char CharString::CharAt(int idx)
{
	int charIdx = CheckIdx(idx);

	return buffer[charIdx];
}

char CharString::FirstSymb()  const
{
	return buffer[0];
}

char CharString::LastSymb()  const
{
	if(length > 0)
		return buffer[length - 1];
	else
		return buffer[length];
}

void CharString::Replace(char oldChar, char newChar)
{
	for(int i = 0; i < length; i++)
	{
		if(buffer[i] == oldChar)
			buffer[i] = newChar;
	}
}

void CharString::DeleteSymb(char c)
{
	int tmp = 0;

	for(int i = 0; i < length; i++)
	{
		if(buffer[i] == c)
			tmp++;
	}

	int len = strlen(buffer) - tmp + 1;

	char* tStr = new char[len];

	for(int i = 0, j = 0; i < len; )
	{
		if(buffer[j] == c)
		{
			j++;
		}
		else
		{
			tStr[i] = buffer[j];
			i++;
			j++;
		}
	}

	tStr[len - 1] = '\0';

	Delete();
	New(tStr);

	delete [] tStr;
}

void CharString::DeleteSpaces()
{
	DeleteSymb(' ');
}

CharString CharString::ToUpperCase()
{
	for(int i = 0; i < length; i++)
	{
		if(buffer[i] >= LOWER_A && buffer[i] <= LOWER_Z)
			buffer[i] -= UP_LOW_DIFF;
		else if(buffer[i] >= LOWER_A_CYR && buffer[i] < 0)
			buffer[i] -= UP_LOW_DIFF;
		else if(buffer[i] == LOWER_YO_CYR)
			buffer[i] = UPPER_YO_CYR;
	}

	return *this;
}

CharString CharString::ToLowerCase()
{
	for(int i = 0; i < length; i++)
	{
		if(buffer[i] >= UPPER_A && buffer[i] <= UPPER_Z)
			buffer[i] += UP_LOW_DIFF;
		else if(buffer[i] >= UPPER_A_CYR && buffer[i] < LOWER_A_CYR)
			buffer[i] += UP_LOW_DIFF;
		else if(buffer[i] == UPPER_YO_CYR)
			buffer[i] = LOWER_YO_CYR;
	}

	return *this;
}

CharString CharString::Reverse()
{
	char* tmp = new char[length + 1];

	for(int i = 0; i < length; i++)
	{
		tmp[i] = buffer[length - i - 1];
	}

	tmp[length] = '\0';


	Delete();
	New(tmp);
	
	delete [] tmp;

	return *this;
}

CharString CharString::Substring(int idx)
{
	int sIdx = CheckIdx(idx);
	int size = length - idx + 1;

	char* tmp = new char[size];

	for(int i = 0; i < size; i++)
		tmp[i] = buffer[sIdx + i];

	CharString tempString(tmp);

	delete [] tmp;

	return tempString;
}

CharString CharString::Substring(int start, int len)
{
	int startIdx	= CheckIdx(start);
	int endIdx		= CheckIdx(startIdx + len);
	
	if(startIdx > endIdx)
		return CharString("");


	int size = endIdx - startIdx + 1;

	char* tmp = new char[size];

	for(int i = 0; i < size; i++)
	{
		tmp[i] = buffer[i + startIdx];
		// Set '\0' to the last element of buffer
		if(i == size - 1)
			tmp[i] = '\0';
	}

	CharString tempString(tmp);

	delete [] tmp;

	return tempString;
}

int CharString::Search(const char* s)
{
	char* tmp = strstr(buffer, s);
	
	if(tmp)
	{
		for (int i = 0; i < length; i++)
			if(tmp == &buffer[i])
				return i;
	}

	return -1;
}

int CharString::Search(const CharString& s)
{
	char* tmp = strstr(buffer, s.ToString());
	
	if(tmp)
	{
		for (int i = 0; i < length; i++)
			if(tmp == &buffer[i])
				return i;
	}

	return -1;
}

int CharString::FindFirst(char c) const
{
	for(int i = 0; i < length; i++)
	{
		if(buffer[i] == c)
			return i;
	}

	return -1;
}

int CharString::FindLast(char c) const
{
	for(int i = 0; i < length; i++)
	{
		int idx = length - 1 - i;

		if(buffer[idx] == c)
			return idx;
	}

	return -1;
}

CharString& CharString::operator = (const CharString& cs)
{
	if(this == &cs)
		return *this;
	
	Delete();
	New(cs.buffer);

	return *this;
}

CharString& CharString::operator = (const char* s)
{
	*this = CharString(s);

	return *this;
}

CharString& CharString::operator = (char c)
{
	char tmp[2] = {0};
	tmp[0] = c;

	*this = CharString(tmp);

	return *this;
}

CharString CharString::operator + (const CharString& cs)
{
	char* tmp = new char[length + cs.length + 1];

	strcpy(tmp, buffer);
	strcat(tmp, cs.buffer);

	Delete();
	New(tmp);

	delete [] tmp;

	return *this;
}

CharString CharString::operator + (const char* s)
{
	int tLen = strlen(s);
	char* tmp = new char[length + tLen + 1];

	strcpy(tmp, buffer);
	strcat(tmp, s);

	Delete();
	New(tmp);

	delete [] tmp;

	return *this;
}

CharString CharString::operator	+ (char c)
{
	int size = length + 2;
	char* tmp = new char[size];

	strcpy(tmp, buffer);

	tmp[size - 2] = c;
	tmp[size - 1] = '\0';

	Delete();
	New(tmp);

	delete [] tmp;

	return *this;
}

bool CharString::operator == (const CharString& cs)
{
	int t = strcmp(this->ToString(), cs.ToString());

	if(t)
		return false;

	return true;
}

bool CharString::operator == (const char* str)
{
	return *this == CharString(str);
}

bool CharString::operator == (char c)
{
	return *this == CharString(c);
}

void CharString::New(const char* s)
{
	length	= strlen(s);

	buffer		= new char[length + 1];

	strcpy(buffer, s);
}

void CharString::Delete()
{
	if(buffer)
		delete [] buffer;

	buffer = NULL;
}

int CharString::CheckIdx(int idx)
{
	int tmp = idx;

	if(tmp < 0)
		tmp = 0;

	else if(tmp > length)
		tmp = length;

	return tmp;
}