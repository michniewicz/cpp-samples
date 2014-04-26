#pragma once

template<typename T>
class Node
{
	T*	data;
	int	key;

	Node*	parent;
	Node*	left;
	Node*	right;

public:
	Node(T* d = NULL,  Node* l = NULL, Node* r = NULL, Node* p = NULL);
	Node(const Node& Nd);
	~Node();

public:
	// get data
	T* GetData() const;
	// set data
	void SetData(T& d);
	// get key
	int GetKey() const;
	// set key
	void SetKey(int k);

	// Get left element pointer
	Node* Left() const
	{
		return left;
	}
	// set left element pointer
	void Left(Node* l)
	{
		left = l;
	}

	// Get right element pointer
	Node* Right() const
	{
		return right;
	}
	// Set next element pointer
	void Right(Node* r)
	{
		right = r;
	}

	// get parent pointer
	Node* Parent() const
	{
		return parent;
	}
	// set parent pointer
	void Parent(Node* p)
	{
		parent = p;
	}

	Node& operator = (const Node& Nd);

private:

	int GenerateHashCode(T* d);
	void ClearPointers();
};

template<typename T>
Node<T>::Node(T* d,  Node* l, Node* r, Node* p)
{
	data	= d;
	key		= GenerateHashCode(d);

	left	= l;
	right	= r;
	parent	= p;

}

template<typename T>
Node<T>::Node(const Node& Nd)
{
	ClearPointers();

	data	= Nd.GetData();
	key		= Nd.GetKey();
	left	= Nd.Left();
	right	= Nd.Right();
	parent	= Nd.Parent();
}

template<typename T>
Node<T>::~Node()
{

}

template<typename T>
T* Node<T>::GetData() const
{
	return data;
}

template<typename T>
void Node<T>::SetData(T& d)
{
	data = d;
	SetKey(GenerateHashCode(d));
}

template<typename T>
int Node<T>::GetKey() const
{
	return key;
}

template<typename T>
void Node<T>::SetKey(int k)
{
	key = k;
}

template<typename T>
Node<T>& Node<T>::operator = (const Node& Nd)
{
	if(this == &Nd)
		return *this;

	ClearPointers();

	data	= Nd.GetData();
	key		= Nd.GetKey();
	left	= Nd.Left();
	right	= Nd.Right();
	parent	= Nd.Parent();

	return *this;
}

template<typename T>
int Node<T>::GenerateHashCode(T* d)
{
	int tmp = (int) *d;

	return tmp;
}

template<typename T>
void Node<T>::ClearPointers()
{

	left	= NULL;
	right	= NULL;
	parent	= NULL;
}