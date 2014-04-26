#pragma once

#include "Node.h"
#include "NoSuchElementException.h"

/// Class List
template <typename T> 
class List
{
	/// First element of the list
	Node<T>* pHead;
	/// Last element of the list
	Node<T>* pTail;

public:
	/// Creates an empty List
	List();

	/// Copy constructor for List
	List(const List& Ls);

	/// Destructor
	virtual ~List();

public:
	/// Returns the number of elements in this list.
	int GetLength() const;

	/// Appends the specified element to the end of this list.
	void Add(const T& d);

	/// Appends the specified element at the beginning of this list.
	void AddHead(const T& d);

	/// Inserts the specified element at the specified position in this list.
	void AddByIndex(const T& d, int idx);

	/// Removes and returns the first element from this list
	T DeleteHead();

	/// Removes and returns the last element from this list
	T DeleteTail();

	/// Removes the element at the specified position in this list.
	T DeleteByIndex(int idx);

	/// Removes all of the elements from this list
	void DeleteAll();

	/// Returns the first element in this list
	T	GetFirst();

	/// Returns the last element in this list.
	T	GetLast();
	
	/// Returns the element at the specified position in this list
	T	Get(int idx);

	/// Overloaded operator = 
	List& operator	= (const List& Ls);
	/// Overloaded operator +
	List operator	+ (const List& Ls);

private:
	/// Initialises fields of class with NULL value
	void Init();

	/// Returns adress of the first element
	Node<T>* GetPHead() const;
	/// Returns adress of the first element
	Node<T>* GetPTail() const;

	/// Copies elements
	void	CopyElements(Node<T>* tmp);
	/// Checks for out of range
	int		CheckValue(int idx);
};


template <typename T>
List<T>::List()
{
	Init();
}

template <typename T>
List<T>::List(const List& Ls)
{
	Init();
	Node<T>* tmp = Ls.GetPHead();
	CopyElements(tmp);
}


template <typename T>
List<T>::~List()
{
	DeleteAll();
}

template <typename T>
int List<T>::GetLength() const
{
	int tmp = 0;
	
	if(!pHead)
		return tmp;

	Node<T>* tNode = pHead;

	while(tNode) 
	{
		tmp++;
		tNode = tNode->Next();
	}

	return tmp;
}

template <typename T>
void List<T>::Add(const T& d)
{

	Node<T>* newNode = new Node<T>(d, pTail);

	if(!pHead)						
		pHead = newNode;

	if(pTail)
		pTail->Next(newNode);

	pTail = newNode;
}

template <typename T>
void List<T>::AddHead(const T& d)
{
	Node<T>* newNode = new Node<T>(d, NULL, pHead);

	if(!pTail)
		pTail = newNode;

	pHead = newNode;

	if(pHead->Next())
		newNode->Next()->Previous(newNode);
}

template <typename T>
void List<T>::AddByIndex(const T& d, int idx)
{
	int nIdx			= CheckValue(idx);

	Node<T>* tmp		= pHead;
	Node<T>* newNode	= new Node<T>(d);

	if(nIdx == 0)
	{
		AddHead(d);
		return;
	}

	for(int i = 0; i < nIdx - 1; i++)
	{
		tmp = tmp->Next();
	}

	newNode->Next(tmp->Next());
	newNode->Previous(tmp);

	if(newNode->Next())
		newNode->Next()->Previous(newNode);

	tmp->Next(newNode);

}

template <typename T>
T List<T>::DeleteHead()
{
	// If there's no head
	if(!pHead)
		throw new NoSuchElementException("NoSuchElementException is thrown");

	Node<T>* tmp = pHead;

	pHead = tmp->Next();

	if(pHead)
		pHead->Previous(NULL);

	T data = tmp->GetData();

	delete tmp;

	if(pHead == NULL)
		pTail = NULL;

	return data;
}

template <typename T>
T List<T>::DeleteTail()
{
	Node<T>* tmp = pHead;

	// If there's no tail
	if(!pTail)
		throw new NoSuchElementException("NoSuchElementException is thrown");

	// if there's only one element at the list
	if(pHead == pTail)
		return DeleteHead();

	while(tmp)
	{
		if(!tmp->Next()->Next())
		{
			Node<T>* newTail = tmp;

			tmp = tmp->Next();

			newTail->Next(NULL);
			// write new value of pTail
			pTail = newTail;

			T data = tmp->GetData();

			delete tmp;

			return data;
			//break;
		}
		tmp = tmp->Next();
	}

}

template <typename T>
T List<T>::DeleteByIndex(int idx)
{
	int tIdx = CheckValue(idx);

	if(!tIdx)
	{
		return DeleteHead();
	}

	else if(tIdx == GetLength() - 1)
	{
		return DeleteTail();
	}

	Node<T>* tmp = pHead;

	for(int i = 0; i < tIdx - 1; i++)
	{
		tmp = tmp->Next();
	}

	Node<T>* toDel = tmp->Next();

	tmp->Next(toDel->Next());

	toDel->Next()->Previous(tmp);

	T data = toDel->GetData();

	delete toDel;

	return data;
}

template <typename T>
void List<T>::DeleteAll()
{
	while(pHead)
		DeleteHead();
}

template <typename T>
T List<T>::GetFirst()
{
	return pHead->GetData();
}

template <typename T>
T List<T>::GetLast()
{
	return pTail->GetData();
}

template <typename T>
T List<T>::Get(int idx)
{
	int tIdx = CheckValue(idx);

	if(!tIdx)
	{
		return GetFirst();
	}

	else if(tIdx == GetLength() - 1)
	{
		return GetLast();
	}

	Node<T>* tmp = pHead;

	for(int i = 0; i < tIdx - 1; i++)
	{
		tmp = tmp->Next();
	}

	return tmp->Next()->GetData();
}

template <typename T>
List<T>& List<T>::operator = (const List& Ls)
{
	if(this == &Ls)
		return *this;

	if(pHead)
		DeleteAll();

	Init();
	
	Node<T>* tmp = Ls.GetPHead();
	CopyElements(tmp);

	return *this;
}

template <typename T>
List<T> List<T>::operator + (const List& Ls)
{

	Node<T>* tmp = Ls.GetPHead();

	List<T> tList = *this;

	while(tmp)
	{
		tList.Add(tmp->GetData());

		tmp = tmp->Next();
	}

	return tList;
}

template <typename T>
void List<T>::Init()
{
	pHead = NULL;
	pTail = NULL;
}

template <typename T>
Node<T>* List<T>::GetPHead() const
{
	return pHead;
}

template <typename T>
Node<T>* List<T>::GetPTail() const
{
	return pTail;
}

template <typename T>
void List<T>::CopyElements(Node<T>* tmp)
{
	while(tmp) 
	{
		this->Add(tmp->GetData());

		tmp = tmp->Next();
	}
}

template <typename T>
int List<T>::CheckValue(int idx) 
{
	int tmp = idx;

	if (tmp < 0)
		tmp = 0;

	else if(tmp > GetLength() - 1)
		tmp = GetLength() - 1;

	return tmp;
}