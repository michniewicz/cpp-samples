#pragma once

/// Class Node
template <typename T> 
class Node
{
	T	data;
	
	Node*	prev;
	Node*	next;

public:
	/// Creates Node object with specified data
	Node(const T& d,  Node* p = NULL, Node* n = NULL);

	/// Copy constructor for Node
	Node(const Node& Nd);

	/// Destructor
	virtual ~Node();

public:

	/// Returns data
	T GetData() const
	{
		return data;
	}

	/// Sets data with specified element
	void SetData(const T& d)
	{
		data = d;
	}

	/// Returns address of the previous element
	Node* Previous() const
	{
		return prev;
	}

	/// Sets address of the previous element
	void Previous(Node* p)
	{
		prev = p;
	}

	/// Returns address of the next element
	Node* Next() const
	{
		return next;
	}

	/// Sets address of the next element
	void Next(Node* n)
	{
		next = n;
	}

	/// overloaded operator =
	Node& operator = (const Node& nd);

private:
	/// Set to NULL fields of class which are pointers
	void ClearPointers();
};


template <typename T>
Node<T>::Node(const T& d,  Node* p, Node* n)
{	
	data = d;
	
	prev = p;
	next = n;

}

template <typename T>
Node<T>::Node(const Node& Nd)
{
	ClearPointers();

	data	= Nd.data;

	next	= Nd.next;
	prev	= Nd.prev;
}

template <typename T>
Node<T>::~Node()
{

}

 template <typename T>
Node<T>& Node<T>::operator = (const Node& nd)
{
	if(this == &nd)
		return *this;

	ClearPointers();

	data	= Nd.data;

	next	= Nd.next;
	prev	= Nd.prev;

	return *this;
}

 template <typename T>
void Node<T>::ClearPointers()
{
	next = NULL;
	prev = NULL;
}