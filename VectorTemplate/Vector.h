#pragma once

template <typename T>
class Vector
{
	T*	buffer;
	int	length;

	// 10 elements by default
	int realLen;

public:

	Vector(int len = 0);

	Vector(const Vector& v);

	~Vector();

	// clear
	void	Clear();
	// clear extra memory
	void	ClearExtraMemory();

	int		Push(const T& val);

	T		Pop();


	void InsertAt(const T& val, int idx);

	void DeleteAt(int idx);

	
	T&		operator[](int idx);
	
	Vector	operator + (const Vector& v);
	
	Vector& operator = (const Vector& v);

	
	bool IsEmpty() 
	{
		if(!length)
			return true;

		return false;
	}

	
	int		GetSize() const 
	{
		return length;
	}

	
	int GetExtraSize() const
	{
		return realLen;
	}

private:
	
	void New(int len);
	
	void Delete();

	// init vector elements with 0
	void SetZero();
	
	void Copy(Vector<T>& dst, const Vector<T>& src, int len, int it = 0);

	
	int CheckValue(int idx);
};

template <typename T>
Vector<T>::Vector(int len)
{
	New(len);
	SetZero();
}

template <typename T>
Vector<T>::Vector(const Vector& v)
{
	New(v.length);
	Copy(*this, v, v.length);
}

template <typename T>
Vector<T>::~Vector(void)
{
	Delete();
}

template <typename T>
void Vector<T>::Clear()
{
	Delete();
}

template <typename T>
void Vector<T>::ClearExtraMemory()	
{
	T* tmpBuffer = new T[length];

	for(int i = 0; i < length; i++)
		tmpBuffer[i] = buffer[i];

	delete [] buffer; 

	buffer = tmpBuffer;

	realLen = length;
}

template <typename T>
int Vector<T>::Push(const T& val)
{

	if(length < realLen)
	{
		buffer[length] = val;
		length++;
	}

	else
	{
		Vector<T> tmp(this->length);

		Copy(tmp, *this, length);

		tmp.buffer[tmp.length] = val;
		tmp.length++;

		this->Delete();

		this->New(tmp.length);

		Copy(*this, tmp, tmp.length);
	}

	return length;
}

template <typename T>
T	Vector<T>::Pop()
{
	Vector tmp(length - 1);

	T val = this->buffer[length - 1];

	Copy(tmp, *this, length - 1);
	
	this->Delete();

	this->New(tmp.length);

	Copy(*this, tmp, tmp.length);
	
	return val;
}

template <typename T>
void Vector<T>::InsertAt(const T& val, int idx)
{
	int tIdx = idx;

	if(tIdx < 0)
		tIdx = 0;
	else if(tIdx >= length)
		tIdx = length;

	Vector<T> tmp(tIdx);

	Copy(tmp, *this, tIdx);

	tmp.Push(val);

	for(int i = tIdx+1; i < this->GetSize()+1; i++)
		tmp.Push(buffer[i-1]);

	this->Delete();
	this->New(tmp.length);

	Copy(*this, tmp, tmp.length);
}

template <typename T>
void Vector<T>::DeleteAt(int idx)
{
	int tIdx = CheckValue(idx);
	

	Vector<T> tmp(tIdx);

	Copy(tmp, *this, tIdx);

	for(int i = tIdx + 1; i < this->GetSize(); i++)
		tmp.Push(buffer[i]);

	this->Delete();
	this->New(tmp.length);

	Copy(*this, tmp, tmp.length);
}

template <typename T>
T& Vector<T>::operator[] (int idx)
{
	int tIdx = CheckValue(idx);

	return buffer[tIdx];
}

template <typename T>
Vector<T> Vector<T>::operator + (const Vector<T>& v)
{
	Vector tmp (this->length + v.length);
	Copy(tmp, *this, this->length);
	Copy(tmp, v, tmp.length, this->length);

	return tmp;
}

template <typename T>
Vector<T>& Vector<T>::operator = (const Vector<T>& v)
{
	if(this == &v)
		return *this;
	
	Delete();

	New(v.length);
	Copy(*this, v, this->length);

	return *this;
}

template <typename T>
void Vector<T>::New(int len)
{
	if(len < 0)
	{
		length = 0;
	}

	if(len > 0)
	{
		this->length	= len;
		realLen			= length*2;
	}
	else
	{
		realLen	= 10;
		length	= 0;
	}

	buffer	= new T[realLen];
}

template <typename T>
void Vector<T>::Delete()
{
	if(buffer)
		delete [] buffer, buffer = NULL;

	length	= 0;
	realLen = 0;
}

template <typename T>
void Vector<T>::SetZero()
{
	for(int i=0; i < length; i++)
		buffer[i] = NULL;
}

template <typename T>
void Vector<T>::Copy(Vector<T>& dst, const Vector<T>& src, int len, int it)
{
	for(int i = it; i < len; i++)
	{
		dst.buffer[i] = src.buffer[i - it];
	}
}

template <typename T>
int Vector<T>::CheckValue(int idx)
{
	int tmp = idx;

	if(tmp < 0)
		tmp = 0;
	if(tmp >= length)
		tmp = length - 1;


	return tmp;
}